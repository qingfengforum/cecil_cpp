#ifndef CLASS_MANAGE_DYNAMIC_MEMORY_H_
#define CLASS_MANAGE_DYNAMIC_MEMORY_H_

#include <iostream>
#include <memory>

using namespace std;

class StrVec{
public:
    StrVec():
        elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec &); // copy constructor
    StrVec(StrVec &&); // move constructor
    StrVec &operator=(const StrVec &); // copy-assignment operators
    ~StrVec();

    void push_back(const std::string &);
    size_t size() const { return first_free - elements;}
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements;}
    std::string *end() const { return first_free;}

private:
    void chk_n_alloc()
        {if (size() == capacity())  reallocate();}
    
    std::pair<std::string*, std::string*> alloc_n_copy
        (const std::string*, const std::string*);
    void free();
    void reallocate();

    std::allocator<std::string> alloc; // allocates the elements
    std::string *elements; // pointer to the first element in the array
    std::string *first_free; // pointer to the first free element in the array
    std::string *cap; // pointer to the one past the end of the array
};


StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec &&s) noexcept :
    elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec::~StrVec()
{
    free();
}

StrVec &StrVec::operator=(const StrVec &s)
{
    // first save the data and then free the data. (considering self assignment)
    auto data = alloc_n_copy(s.begin(), s.end());
    free();

    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    // construct a copy of s in the element to which the first_free points
    alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*> 
StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    // allocate space to hold as many elements as are in the range
    auto data = alloc.allocate(b-e);
    // initialize and return a pair constructed from data and the value returned by uninitialized_copy 
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if (elements)
    {
        for (auto p = first_free; p != elements; /*empty*/)
        {
            // destroy the data
            alloc.destroy(--p);
        }
        // free the space.
        alloc.deallocate(elements, cap-elements);
    }
}

void StrVec::reallocate()
{
    auto newcapacity = size()? size()*2 : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i < size(); ++i)
    {
        alloc.construct(dest++, std::move(*elem++));
    }

    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}


#endif