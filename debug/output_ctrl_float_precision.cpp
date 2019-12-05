#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

int main()
{
    float f = 3.141592653;
    float fs = 3.2;
    /* C ways */
    printf("-------- C ------------\n");
    printf("f(5): %.5f \n", f);   // 3.14159
    printf("f(7): %.7f \n", f);   // 3.141592653
    printf("f(7): %.7f \n", fs);  // 3.2000000
    printf("f(7): %03.f \n", fs); // 003
    printf("f(7): %010.7f \n", fs); // 03.2000000

    /* c++ ways */
    cout << "------------ c++ -----------" << endl;
    cout << "f : " << f << endl;
    cout << setiosflags(ios::fixed); // to ensure the fixed is after the decimal point
    cout << setprecision(7);
    cout << "f(7): " << f << endl;
    cout << "fs(7): " << fs << endl;
}