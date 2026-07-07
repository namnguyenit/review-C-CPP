#include <iostream>
#include <string>
#include "include/stack.hpp"

using namespace std;

int main(){
    try
    {
        Stack<int> intStack;
        intStack.push(10);
        intStack.push(20);
        intStack.push(30);
        cout<< "Kich thuoc: " << intStack.size()<< endl;
        while(!intStack.isEmpty()){
            cout<< "Phan tu: ";
            cout<< intStack.top()<< ", ";
            intStack.pop();
        }
        cout<< endl;
        Stack<string> strStack;
        strStack.push("Hello");
        strStack.push("Xin");
        strStack.push("Chao");
        cout<< "Kich thuoc: " << strStack.size()<< endl;
        while(!strStack.isEmpty()){
            cout<< "Phan tu: ";
            cout<< strStack.top()<< ", ";
            strStack.pop();
        }
        cout << endl;
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
    
}
