/*
 * =====================================================================================
 *
 *       Filename:  examples.cpp
 *
 *    Description:  examples in books
 *
 *        Version:  1.0
 *        Created:  08/07/2015 00:33:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::string;

int power(int, int);
void constructStr();
void readwriteStr();
void getlineStr();
string s;
int main(){
    getlineStr();
    return 0;
}

int power(int x, int n){
    if (1 == n)
        return x;
    else
        return x * power(x, n-1);
}

void constructStr(){
    string s1; // 默认的构造函数 s1为空串 构造函数用来初始化一个对象
    string s2(s1); //将s2初始化为s1的一个copy
    string s3("value"); //赋初值
    //string s4(n, 'c'); // ?

}

void readwriteStr(){
    string s;
    cin >> s; //忽略开头所有的空白,直到再次遇到空白
    cout << s << endl;

    //这些操作返回左操作数
    string s1, s2;
    cin >> s1 >> s2;
    cout << s1 << s2;

}

void getlineStr(){
    string s;
    while (getline(cin, s)) // 返回值是 istram ,err或者eof停止
    //istream& getline (istream& is, string& str, char delim);
        cout << s << endl;

}
