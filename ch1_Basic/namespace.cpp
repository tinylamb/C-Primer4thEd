/*
 * =====================================================================================
 *
 *       Filename:  namespace.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/02/2016 23:41:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
/* include files */
#include <iostream>
#include <string>
using namespace std;
namespace mystring
{

    class string{ 
        public:
            string(){
                cout << "test mystring" << endl;
            }
            ~string(){}
    };
}

using namespace mystring;
int main(){
    mystring::string s;
    return 0;
}
/* 
 * namespace.cpp: In function ‘int main()’:
namespace.cpp:35:5: error: reference to ‘string’ is ambiguous
     string s;
     ^
namespace.cpp:24:11: note: candidates are: class mystring::string
     class string{
           ^
In file included from /usr/local/Cellar/gcc49/4.9.2_1/include/c++/4.9.2/iosfwd:39:0,
                 from /usr/local/Cellar/gcc49/4.9.2_1/include/c++/4.9.2/ios:38,
                 from /usr/local/Cellar/gcc49/4.9.2_1/include/c++/4.9.2/ostream:38,
                 from /usr/local/Cellar/gcc49/4.9.2_1/include/c++/4.9.2/iostream:39,
                 from namespace.cpp:18:
/usr/local/Cellar/gcc49/4.9.2_1/include/c++/4.9.2/bits/stringfwd.h:62:33: note:                 typedef class std::basic_string<char> std::string
   typedef basic_string<char>    string; */

