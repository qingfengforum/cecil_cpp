#ifndef TEXT_QUERY_REVISITED_H_
#define TEXT_QUERY_REVISITED_H_

#include <iostream>
#include <memory>

class QueryResult {};
class TextQuery {
public:
    typedef size_t line_no;

    QueryResult query(const std::string &s);
};

// abstract class acts as a base class of concrete query types; all members are private
class Query_base{ // abstract base class
    friend class Query;
protected:
    using line_no = TextQuery::line_no; // define a type alias
    virtual ~Query_base() = default; // 
private:
    virtual QueryResult eval(const TextQuery&) const = 0; // pure virtual function;
    virtual std::string req() const = 0; // pure virtual function;
};

// interface class to manage the Query_base inheritance hierarchy
class Query{
    // these operator need to access shared_ptr constructor.
    friend Query operator~(const Query &);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);

public:
    Query(const std::string &); // build a new WorldQuery
    // interface functions:call the corresponding Query_base operations
    QueryResult eval(const TextQuery &t) const
        { return q->eval(t);}
    std::string rep() const {return q->req();}

private:
    Query(std::shared_ptr<Query_base> query): q(query) { }
    std::shared_ptr<Query_base> q;
};

std::ostream& operator<<(std::ostream& os, const Query & query)
{
    return os << query.rep();
}


class WordQuery : public Query_base {
    friend class Query; // Query use WordQuery constructor
    WordQuery(const std::string &s) : query_word(s) {}

    QueryResult eval(const TextQuery &t) const 
    { return t.query(query_word);}

    std::string rep() const {return query_word;}

    std::string query_word; // word for which to search
};


inline
Query::Query(const std::string &s) : q(new WordQuery(s)) {}

class NotQuery: public Query_base {
    friend Query operator~(const QUery &);
    NotQuery(const Query &q) : query(q) {}

    QueryResult eval(const TextQuery &) const;
    std::string rep() const {return "~(" + query.rep() + ")";}

    Query query;
};

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery: public Query_base{
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s) : 
        lhs(l), rhs(r), opSym(s) {}

    std::string rep() const {return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";}

    Query lhs, rhs;
    std::string opSym; // name of the operator
};

class AndQuery: public BinaryQuery {
    friend Query operator&(const Query&, const Query&);

    AndQuery(const Query &left, const Query & right) : 
                    BinaryQuery(left, right, "&") {}
    QueryResult eval(const TextQuery&) const ;
};
inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery: public BinaryQuery {
    friend Query operator|(const Query&, const Query&);

    OrQuery(const Query &left, const Query &right) : 
        BinaryQuery(left, right, "|") {}
    QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult
OrQuery::eval(const TextQuery& text) const
{
    auto right = rhs.eval(text);
    auto left = lhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());

    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult
AndQuery::eval(const TextQuery& text) const
{
    auto left = lhs.eval(text);
    auto right = rhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>();
    set_intersection(left.begin(), left.end(),
                right.begin(), right.end(),
                    insert(*ret_lines, ret_lines->begin()));
    
    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult
NotQuery::eval(const TextQuery& text) const
{
    auto result = query.eval(text);
    auto ret_lines = make_shared<set<line_no>>();

    auto beg = result.begin(), end = result.end();
    auto sz = result.get_file()->size();
    for (size_t n = 0; n  != sz; ++n)
    {
        if (beg == end || *beg != n)
        {
            ret_lines->insert(n);
        }
        else if (beg != end)
        {
            ++beg;
        }
    }

    return QueryResult(rep(), ret_lines, result.get_file());
}

#endif