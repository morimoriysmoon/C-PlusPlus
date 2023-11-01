#include <iostream>

using namespace std;

class Empty
{
};

class Dummy
{
public:
    Dummy(int _idx) : index(_idx) {}

    /**
        copy constructor의 파라미터가 Dummy rhs라면 컴파일러가 불평한다.
        왜냐하면 파라미터가 복사되는 과정에서 복사 생성자가 다시 불리기 때문에
		recursive function이 되어 stackoverflow가 발생한다.
        괜히 const Dummy&를 사용하는 것이 아니다.
    */
    Dummy(const Dummy& rhs)
    {
        this->index = rhs.index;
    }

    int getIndex(void) { return index; }

private:
    int index;
};


int main()
{
    cout << "Hello world!" << endl;

    /**
        빈 class의 사이즈는 0이 아니라 1이다. 컴파일러가 1바이트 char를 몰래 삽입한다.
        왜냐하면 메모리 어딘가에서 공간을 점유해야 접근이 가능하기 때문에.
    */
    cout << "The size of empty class is : " << sizeof(Empty) << endl;

    return 0;
}
