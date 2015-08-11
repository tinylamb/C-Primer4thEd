#include <iostream>
#include <string>
#include <map>
using namespace std;

int getid(string, string);

int main(){
    string s = "gaoyang,3|xiaohua,44|caicai,52131|";
    cout << "id : " << getid("caicai", s) << endl;
    /*  
    string sub1;
    string sub2;
    map<string, int> dict;
    size_t p;
    p = s.find(",");
    sub1 = s.substr(0, p);
    sub2 = s.substr(p+1);
    //atoi(str.c_str())
    //dict[sub1] = atoi(sub2.c_str());
    dict.insert(map<string, int>::value_type(sub1, atoi(sub2.c_str())));  字典的正确赋值方式
    //dict.insert(sub1, atoi(sub2.c_str()));
    cout << "find position " << p << endl;
    cout << "sub1 string : " << sub1 << endl;
    cout << "sub2 string : " << sub2 << endl;
    cout << "string dict :" << dict[sub1] << endl;
    */

    return 0;

}

int getid(string pin, string white){
    size_t pin_p, comma_p, delim_p;
    size_t len;
    len = white.size();
    cout << "len of white is : " << len << endl;

    //将string 转化为 c 的字符串数组
    //const char *p = white.c_str();
    pin_p = white.find(pin);
    //cout << "pin_p : " << pin_p << endl;
    if(pin_p != string::npos){
        comma_p = white.find(",", pin_p);
        delim_p = white.find("|", pin_p);
        string id = white.substr(comma_p + 1, delim_p -1 - comma_p);
        //cout << "id string : " << id << endl;
        return atoi(id.c_str());
    }
    else
        return -1;


}
