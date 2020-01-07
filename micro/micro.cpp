#include <iostream>

using namespace std;

/* 
 * #var 
 *      : make var as a string. ==> "var"
 * */
#define VAR_NAME(name) (#name)

/*
 * ##var
 *      : if "args..." is empty then ==> printf("debug [%s] : " format, __FUNCTION__)
 *      : if "args..." is not empty then ==> printf("debug [%s] : " format, __FUNCTION__, ##args) 
 * */
#define LOG_DEBUG(format, args...) \
    { \
        printf("debug [%s] : " format, __FUNCTION__, ##args); \
    }

/* apply of #var */
#define NAME(X) #X
#define OUT(X)  { \
                    std::string xname = NAME(X); \
                    std::cout << xname << ":" << X << std::endl; \
                }

int main()
{

    int test_a = 0;

    cout << VAR_NAME(test_a) << endl; // output : test_a
    cout << NAME() << endl;

    LOG_DEBUG("hello world: %d\n", test_a);

    OUT(test_a);

    return 0;
}