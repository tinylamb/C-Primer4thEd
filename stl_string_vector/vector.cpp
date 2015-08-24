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
#include <stdexcept>
using namespace std;

void outofrange();
void vectorrefer(vector<int> &vec);

int main(){
    vector<int> v(10);
    vectorrefer(v);
    cout << "vec value of v(0) : " << v.at(0) << endl;
    return 0;
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
