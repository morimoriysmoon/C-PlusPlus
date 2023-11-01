#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    /// 1> float이 메모리에 저장되는 방법에 대하여

    float fno = 43.25f;

    printf("[x] 43.25 = %x\n", *(unsigned int*)(&fno)); /// 422d0000h = 0b + 10000100b + 01011001000000000000000b


    /// 2> float 연산의 오차에 대하여

    cout << "size of float : " << sizeof(float) << endl;
    cout << "size of double : " << sizeof(double) << endl;

    float fdelta = 0.1f;
    float fsum = 0.0f;

    double ddelta = 0.1;
    double dsum = 0.0;

    /// for문의 반복회수가 증가할 수록 오차가 증가함.
    /// 주의 : 반복회수가 적으면 정확한 값인 것처럼 보인다.

    for(int i = 0 ; i < 1000000 ; ++i)
    {
        fsum += fdelta;
        dsum += ddelta;
    }

    cout << "fsum = " << fsum << endl;
    cout << "dsum = " << dsum << endl;

    return 0;
}
