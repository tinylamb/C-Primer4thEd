#include <iostream>
#include <cstdlib>
#include <numeric>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void floatcompute();

void transform();

void unsignedtoint();
int main(){
    unsignedtoint();
}

void floatcompute(){
    uint32_t x, y;
    x = 1;
    y = 10;
    float ctr, ctr1;
    ctr = (float)(x) / y;
    ctr1 = static_cast<float>(x) / y;
    
    cout << "float ctr : " << ctr << endl << "ctr1 : "<< ctr1 <<endl;

}

void transform(){
    vector<float> v, v2(7), v3(7);
    vector<float>::iterator iter, iter2, iter3;
    //ππ‘Ïv1
    for(int i = 1; i < 6; i++)
        v.push_back(i + 0.0);

    vector<float> diff(v.size());
    float sum = std::accumulate(v.begin(), v.end(), 0.0);
    float mean = sum / v.size();

    cout << "v : " << endl;
    for(iter = v.begin(); iter != v.end(); ++ iter)
        cout << (*iter) << " ";
    cout << endl;

    std::transform(v.begin(), v.end(), diff.begin(), 
            std::bind2nd(std::minus<float>(), mean));
    cout << "diff : " << endl;
    for(iter = diff.begin(); iter != diff.end(); iter ++)
        cout << *iter << " ";
    cout << endl;






}

void unsignedtoint(){
    int iInt;
    uint32_t dwI = 10, dwJ = 20, dwK;
    iInt = dwI - dwJ;
    dwK = dwI - dwJ;
    cout << iInt << endl;
    cout << dwK << endl;
}
