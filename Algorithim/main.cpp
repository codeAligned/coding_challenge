#include <iostream>

using namespace std;



int GetDataTypeLength();
int main()
{
    cout << "Hello world!" << endl;

    GetDataTypeLength();
    return 0;
}

int GetDataTypeLength()
{
    char charVar = 'c';
    bool boolVar = false;
    int intVal = 42;
    short shortVal = 42;
    long longVal = 42;
    unsigned long long ullVal = 44444;

    float fVal = 67.8;
    double dVal = 55.4;
    long double ldVal = 88.9;

    std::cout << "char size is " << sizeof(charVar) << std::endl;
    std::cout << "bool size is " << sizeof(boolVar) << std::endl;
    std::cout << "int size is " << sizeof(intVal) << std::endl;
    std::cout << "short size is " << sizeof(shortVal) << std::endl;
    std::cout << "long size is " << sizeof(longVal) << std::endl;
    std::cout << "unsigned long long size is " << sizeof(ullVal) << std::endl;
    std::cout << "float size is " << sizeof(fVal) << std::endl;
    std::cout << "double size is " << sizeof(dVal) << std::endl;
    std::cout << "long double size is " << sizeof(ldVal) << std::endl;
    return 0;


}



