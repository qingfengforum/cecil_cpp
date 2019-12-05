#include <iostream>
#include <string>

#define Name(X) #X
#define OUT(X) { \
                    std::string xname = Name(X); \
                    std::cout << xname << " : " << X << std::endl; \
                }

struct Temp{
    int i;
    std::string s;
};

int main()
{
    Temp tmp;
    tmp.i = 10;
    tmp.s = "this is a test";

    OUT(tmp.i);
    OUT(tmp.s);

    return 0;
}