#include <iostream>
#include <string>
using namespace std;

void string_empty();

int main(){
    string_empty();
}

void string_empty(){
    string s1 = "";
    string s2 = "gaoyang";
    string s;
    s = (s1.empty())?s2:s1;
    if (s == "gaoyang")
        cout << s << "==" << "gaoyang" << endl;
}
