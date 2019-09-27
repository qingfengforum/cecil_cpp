#ifndef COPY_CONTROL_AND_RESOURCE_MANAGEMENT_H_
#define COPY_CONTROL_AND_RESOURCE_MANAGEMENT_H_

//#define VALUE_LIKE (1) // valuelike with pointerlike
#define POINTER_LIKE (1)

#ifdef VALUE_LIKE
Class HasPtr{
public:
    // constructor
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)),i(0) {}
    
    // copy constructor (valuelike)
    HasPtr(const HasPtr &p):
        ps(new std::string(*p.ps)), i(p.i) {}
    HasPtr &operator=(const HasPtr &p);
    ~HasPtr() {delete ps;}

private:
    std::string *ps; // point to the resource
    int i;
};

/*
* 1. constructor
* 2. desturctor 
* 3. copy
*/
HasPtr &HasPtr::operator=(const HasPtr &rhs)
{   
    auto newp = new std::string(*rhs.ps); //  copy the underlying string;
    delete ps; // free the old string;
    ps = newp; // copy data from rhs to this object
    i = rhs.i;
    return *this; // return this object
}

#elif defined(POINTER_LIKE)
class HasPtr{
public:
    HasPtr(const std::string &s):
        ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
    HasPtr(const HasPtr &p):
        ps(p.ps), i(p.i), use(p.use) {++*use;}
    HasPtr &operator=(cosnt HasPtr &p);
    ~HasPtr();

    friend void swap(HasPtr&, HasPtr&);

private:
    std::string *ps;
    int i;
    std::size_t *use; // member to keep track of how many objects share *ps;
};

HasPtr::~HasPtr()
{
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
}

HasPtr &operator=(cosnt HasPtr &rhs)
{
    ++*rhs.use; // increment the use count of the right-hand operand
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }

    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;

    return *this;
}

inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps); // swap the pointer, not the string data
    swap(lhs.i, rhs.i); // swap the int member
}

#endif

#endif