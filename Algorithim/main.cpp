#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

using AINT = int;

int GetDataTypeLength();
auto GetPartialArry(int (*raw_array)[4]) -> int (*)[2];
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
    AINT intVal = 42;
    short shortVal = 42;
    static long longVal = 42;
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

    std::cout << "const  size is " << sizeof(u'r')<< std::endl;

    const int &bufSize = 512.845;
    std::cout << "const  size is " << sizeof(bufSize)<< std::endl;

    constexpr int ff = 89;
    constexpr long *pLong = &longVal;

    auto val = 88.6;
    cout<< val <<endl;


    std::vector<int> vecLong{5,6,7,8};

    decltype(vecLong.begin()) iter = vecLong.begin();

    cout << "iter size is "<< sizeof(iter) <<endl;
    int * a = NULL;


    cout << "POINT size is "<< sizeof(a) <<endl;


    int nArray[] = {4,5,6};

    int *pNArray = begin(nArray);
    cout << pNArray << endl;

    auto pArray = &nArray;

    cout << (*pArray)[1] <<endl;

    int bArray[4] = {7,8,9,10};
    int (*pTwoArr)[2] = NULL;

    pTwoArr = GetPartialArry(&bArray);
    cout << (*pTwoArr)[0] <<endl;
    cout << (*pTwoArr)[1] <<endl;
    cout << (*(pTwoArr+1))[0] <<endl;
    cout << (*(pTwoArr+1))[1] <<endl;


    cout << istream::eofbit << endl;
    cout << istream::goodbit << endl;
    cout << istream::failbit << endl;
    cout << istream::badbit << endl;

    cout << cout.eof() << endl;

    cout << endl;

    fstream tempIO;
    fstream::iostate tempIOState = fstream::eofbit;
    tempIO.setstate(tempIOState);
    cout << tempIO.rdstate() << endl;
    tempIO.clear(tempIOState);
    cout << tempIO.rdstate() << endl;
    tempIO.clear();
    cout << tempIO.rdstate() << ends;
    cout << tempIO.rdstate() << ends;
    return 0;
}









auto GetPartialArry(int (*raw_array)[4]) -> int (*)[2]
{
    int (*pPartialArray)[2] = NULL;
    pPartialArray = (int (*)[2])raw_array;
    return pPartialArray;
}



