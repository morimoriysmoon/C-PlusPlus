#include <iostream>

using namespace std;


template<unsigned n>
struct Factorial
{
    enum { value = n * Factorial<n-1>::value };
};


/**
    recursive 동작을 정지시키기 위한 특수화 버전
*/
template<>
struct Factorial<0>
{
    enum { value = 1 };
};

int main()
{
    cout << "Hello world!" << endl;

    cout << Factorial<5>::value << endl;

    return 0;
}
