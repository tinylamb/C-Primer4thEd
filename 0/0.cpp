#include <iostream>
using namespace std;

void PrintInterval();

int main(){
    PrintInterval();
    return 0;
}

void PrintInterval(){
    int a, b;
    std::cout << "input two integers : " << std::endl;
    cin >> a >> b;
    int i = a;
    while(i <= b){
        std::cout << i << std::endl;
        ++i;
    }
}
