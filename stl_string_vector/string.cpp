#include <iostream>
#include <string>
#include <sstream>
//#include <stdlib.h>
#include <cstdlib>
using namespace std;

void string_empty();
void num_to_string();
void string_add();
void string_to_uint32();

int main(){
//    string_empty();
    string_to_uint32();
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

void string_add(){
    string list = "gaoyangx,1|gaoyang,2";
    string g = "gaoyang";
    size_t p = list.find(g + ",");
    cout << "position : " << p << endl;

}

void string_to_uint32(){
    string sNum = "n1234name56789";
    char *t;
    uint32_t dwNum = strtoul(sNum.c_str(), &t, 10);
    if(sNum == t){
        cout << "failed." << endl;
        cout << "dwNum :" << dwNum; //失败的话dwNum ＝ 0
    }
    else{
        cout << "dwNum : " << dwNum << endl;
        if((*t) != '\0')
            cout << "last : " << t << endl;
    }

    //取值的范围 0 ~ 2^32-1
    //123name45678 返回123  t指针指向字符n

}
