/*
 * inheritance and dynamic binding
 * */
#ifndef INHERITANCE_DYNAMIC_BINDING_H_
#define INHERITANCE_DYNAMIC_BINDING_H_

#include <iostream>
#include <set>
#include <memory>

/* base class */
class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : 
        bookNo(book), price(sales_price) {}
    std::string isbn() {return bookNo;}
    // returns the total sales price for the specified number of items
    // derived classes will override and apply different discount algorithms
    virtual double net_price(std::size_t n) const
        {return n*price;}
    virtual ~Quote()=default; // dynamic binding for the destructor

    virtual Quote* clone() const & {return new Quote(*this);}
    virtual Quote* clone() && {return new Quote(std::move(*this));}

private:
    std::string bookNo;
protected:
    double price = 0.0; 
};


class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double p, std::size_t qty, double disc) : 
        Quote(book, p), min_qty(qty), discount(disc) {}

    Bulk_quote* clone() const & {return new Bulk_quote(*this);}
    Bulk_quote* clone() && {return new Bulk_quote(std::move(*this));}

    double net_price(std::size_t) const override;

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

double Bulk_quote::net_price(std::size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1-discount) * price;
    else 
        return cnt * price;
}



/*
Derived-to-Base conversion

Quote item;
Bulk_quote bulk;
Quote *p = &item; // p point to Quote object
p = &bulk; // p point to Quote part of bulk
Quote &r = bulk; // r bound to  Quote part of bulk

*/


class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, 
                double disc) :
                    Quote(book, price), 
                    quantity(qty), 
                    discount(disc) 
                    {}
    
    double net_price(std::size_t) const = 0; // pure virtual function

protected: // may be used by derived class
    std::size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote2 : public Disc_quote {
    Bulk_quote2() = default;
    Bulk_quote2(const std::string &book, double price, std::size_t qty, double disc):
        Disc_quote(book, price, qty, disc) {}
    double net_price(std::size_t qty) const override;
};


class Backet{
public:
    void add_item(const std::shared_ptr<Quote> &sale)
    { items.insert(sale); }

    void add_item(const Quote& sale)
    { items.insert(std::shared_ptr<Quote>(sale.clone()));}
    void add_item(Quote&& sale)
    { items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));}

    double total_receipt(std::ostream& ) const;

private:
    static bool compare(const std::shared_ptr<Quote> &lhs, 
                        const std::shared_ptr<Quote> &rhs) 
    {return lhs->isbn() < rhs->isbn();}

    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};

double Backet::total_receipt(std::ostream& os) const
{
    double sum = 0.0;
    for (auto iter = items.cbegin();
            iter != items.cend();
            iter = items.upper_bound(*iter)) // not next item, is next key
    {
        sum += print_total(os, **iter, items.count(*iter));
    }

    os << "Total Sale: " << sum << endl;

    return sum;

}

#endif