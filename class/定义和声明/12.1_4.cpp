#include <iostream>
using namespace std;
class Person{
    private:
        std::string name;
        std::string address;
    public:
        //���캯���ǹ��г�Ա����,û�з���ֵ����
        //Person(std::string, std::string);
        Person(std::string n, std::string a);
        //������Ա��Ա��������Ϊconst����ú����������޸�������ݳ�Ա
        //��Ϊһ�����õı�̷��������һ����Ա����ʱ�����ó�Ա�������������ݳ�Ա�����޸Ĳ�����Ӧ�����ܽ��ó�Ա��������Ϊconst ��Ա����
        string getName() const;
        string getAddress() const;

};
Person::Person(std::string n, std::string a){
    name = n;
    address = a;
}
//ע��������﷨
//�����д�� Person:: string getName()
//��Ա������һ�����ӵ�����ʵ�� thisָ��?
string Person::getName() const{
    return name;
}
string Person::getAddress() const{
    return address;
}
