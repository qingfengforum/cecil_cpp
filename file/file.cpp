#include <iostream>
#include <fstream>

using namespace std;

#define TEST_FILE "test.txt"

int main()
{
    /* *****************
    ** output to file **
    ********************/
    /* output string */
    // open
    ofstream of("test.txt", ios_base::app);
    if (!of.is_open())
    {
        cout << "open failed!!" << endl;
    }

    // output stream
    of << "hello , this is string output to file!" << endl;
    
    // close
    of.close();
}