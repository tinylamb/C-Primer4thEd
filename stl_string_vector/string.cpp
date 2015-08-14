#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void string_empty();
void num_to_string();

int main(){
//    string_empty();
    num_to_string();
    return 0;
}

void string_empty(){
    string s1 = "";
    string s2 = "gaoyang";
    string s;
    s = (s1.empty())?s2:s1;
    if (s == "gaoyang")
        cout << s << "==" << "gaoyang" << endl;
}

void num_to_string(){
    string s;
    uint32_t dwInteger;
    dwInteger = 2134242112;
    ostringstream ss;
    ss << dwInteger;
    s = ss.str();
    cout << s << endl;
    //s += 4.5;

}
