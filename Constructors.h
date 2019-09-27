#ifndef CONSTRUCTORS_H_
#define CONSTRUCTORS_H_

/**
 * 
 * -----------------------------------------------------------
 * the synthesized constructors by the compiler(if not define)
 * -----------------------------------------------------------
 * 1. default constructor (if not define other constructors)
 * 2. copy constructor (even if defined user's copy constructors)
 * 
*/

class Foo {
    Foo(); // default constructor

    /* copy constructor */
    /**
     * memberwise copies
     * copy initialization <-- copy/move constructor
    */
    // synthesized copy constructor
    Foo(const Foo&); // user defined copy constructor
};

#endif