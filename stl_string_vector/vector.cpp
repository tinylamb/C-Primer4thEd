/*
 * =====================================================================================
 *
 *       Filename:  vector.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/18/2015 14:16:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <stdint.h>
using namespace std;

void outofrange();
void vectorrefer(vector<int> &vec);
void vectorpushback();

class CInfo{
    public:
        CInfo():m_sName("lambda"), m_dwAge(25){}
        CInfo(string sName, uint32_t dwAge){
            m_sName = sName;
            m_dwAge = dwAge;
        }
    public:
        string m_sName;
        uint32_t m_dwAge;


};

int main(){
    vectorpushback();
}

void outofrange(){
    std::vector<int> myvector(10);
    try{
        myvector.at(10) = 100;
    }
    catch(const std::out_of_range& oor){
        std::cerr << "out of range error : " << oor.what() << std::endl;
    }

}

void vectorrefer(vector<int> &vec){
    vec.at(0) = 1;
}

void vectorpushback(){
    vector<CInfo> vPerson;
    CInfo oPerson;//如果构造函数没有指定是public 这里会提示调用了private成员
    for(uint32_t index = 0; index < 10; ++index){
        oPerson.m_dwAge = index;
        vPerson.push_back(oPerson);//从输出结果看push_back是值拷贝
    }
    vector<CInfo>::const_iterator iter;
    for(iter = vPerson.begin(); iter != vPerson.end(); ++iter){
        cout << iter->m_sName << " " << iter->m_dwAge << endl;

    }
}


