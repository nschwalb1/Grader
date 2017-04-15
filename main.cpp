#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;
//#include "classroom.h"

int hashfunc(string name){
    char first = name[0];
    int x = toupper(first) - 64;
    return x;
}

int main() {
    //Class myClass;
    string a = "SMITH";
    string b = "SMITI";
    string c;
    for (int i = 0; i < b.length();i++){
        c+= toupper(b[i]);
    }
    int x = b.compare(a);
    std::cout << x << std::endl;
    return 0;
}