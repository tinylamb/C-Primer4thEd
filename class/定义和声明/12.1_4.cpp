#include <iostream>
using namespace std;
class Person{
    private:
        std::string name;
        std::string address;
    public:
        //构造函数是公有成员函数,没有返回值类型
        //Person(std::string, std::string);
        Person(std::string n, std::string a);
        //若将成员成员函数声明为const，则该函数不允许修改类的数据成员
        //作为一种良好的编程风格，在声明一个成员函数时，若该成员函数并不对数据成员进行修改操作，应尽可能将该成员函数声明为const 成员函数
        string getName() const;
        string getAddress() const;

};
Person::Person(std::string n, std::string a){
    name = n;
    address = a;
}
//注意这里的语法
//错误的写法 Person:: string getName()
//成员函数有一个附加的隐含实参 this指针?
string Person::getName() const{
    return name;
}
string Person::getAddress() const{
    return address;
}
