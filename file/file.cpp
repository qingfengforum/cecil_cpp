#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;

#define TEST_FILE "test.txt"

/* file exist */
bool fileExist_fstream(const string &filename);
bool fileExist_stat(const string &filename); // Recommended for file exist.
bool fileExist_access(const string &filename);

/* create file */
bool createFile_ofstream(const string &filename);

/* read from file */
bool readFile_ifstream(const string &filename);

/* write to file */
bool writeFile_ofstream(const string &filename);

int main()
{
#if 0
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

    /*
     * check file exist 
    */

   fstream f("file_exist.txt");
   if (!f.good())
   {
       cout << "file not exist" << endl;
   }
   else
   {
       cout << "file exist" << endl;
   }
#endif   

}

/*
 * it is not a good way to judge if a file exist.
 * but it can return if the file can be opened on your will.
 */
bool fileExist_fstream(const string &filename)
{
    fstream file(filename); // (rw)
    if (file)
    {
        cout << filename << " (rw): open successed" << endl;
        return true;
    }
    else
    {
        cout << filename << " (rw): open failed!" << endl;
        return false;
    }
    
    /*
     * you can also use:
     * ifstream ifile(filename); ==> (r) if the file can be read
     * ofstream ofile(filename); ==> (w) if the file can be write or created.
     * fstream file(filename, ios::in); ==> (r) if the file can be read
     * fstream file(filename, ios::out); ==> (w) if the file can be write or created.
     * */
}

/*
 * #include <unistd.h>
 * */
bool fileExist_access(const string &filename)
{
    // F_OK tests for the existence of the file.
    if (access(filename.c_str(), F_OK) != -1)
    {
        cout << filename << " exist" << endl;
        return true;
    }
    else
    {
        cout << filename << " not exist" << endl;
        return false;
    }
}

/*
 * #include <sys/stat.h>
 * */
bool fileExist_stat(const string &filename)
{

    struct stat buffer;
    if (stat (filename.c_str(), &buffer) == 0)
    {
        cout << filename << " exist" << endl;
        return true;
    }
    else
    {
        cout << filename << " not exist" << endl;
        return false;
    }

}

bool createFile_ofstream(const string &filename)
{
    ofstream ofile(filename);
    if (ofile)
    {
        cout << filename << ": open or create success!" << endl;
        return true;
    }
    else
    {
        cout << filename << ": open or create failed!" << endl;
        return false;
    }
}

/*
 * #include <fstream>
 * #include <sstream>
 * */
bool readFile_ifstream(const string &filename)
{
    ifstream ifile(filename);
    if (!ifile)
    {
        cout << filename << " : open filed!" << endl;
        return false;
    }

    /* read all the info to a string */
    ostringstream tmp;
    tmp << ifile.rdbuf();

    string licence_str = tmp.str();

    /* */
}

bool writeFile_ofstream(const string &filename)
{
    std::ofstream ofile(filename);
    if (!ofile) 
    {
        cout << filename << " : open filed!" << endl;
        return false;
    }

    /* write string to a file */
    std::string w_str;
    w_str = "hello world";

    ofile << w_str;
    
}