#include <iostream>

using namespace std;


class Foo
{
public:
    Foo(const string& _name, const int _id, const unsigned long _arrsize);
    ~Foo();

    Foo& operator=(const Foo& rhs);

    /// 아래 대입연산자는 매개변수로 참조자가 아니라,
    /// 복사 생성자를 사용한 사본을 이용하고 있다.
    /// 어쩌면 컴파일러가 더 효율적인 코드를 만들어 줄 수도 있다.
    //Foo& operator=(Foo rhs);

private:
    string mName;
    int mId;
    int* mPtrInts;
    unsigned long mSize;
};

Foo::Foo(const string& _name, const int _id, const unsigned long _arrsize)
    :mName(_name)
    ,mId(_id)
    ,mPtrInts(nullptr)
    ,mSize(_arrsize)
{
    mPtrInts = new int[mSize];
    for(unsigned int i = 0 ; i < mSize ; ++i)
    {
        mPtrInts[i] = 0;
    }
}

Foo::~Foo()
{
    if(mPtrInts != nullptr)
    {
        delete [] mPtrInts;
    }
}

Foo& Foo::operator=(const Foo& rhs)
{
    /// 매번 아래의 조건문을 실행하는 것이 성능을 나쁘게 만들 수 있다.

    if(this == &rhs)
    {
        cout << "not allowed to copy itself" << endl;
        return *this;
    }

    this->mName = rhs.mName;
    this->mId = rhs.mId;
    this->mSize = rhs.mSize;

    if(rhs.mPtrInts != nullptr)
    {
        delete [] this->mPtrInts;

        this->mPtrInts = new int[this->mSize];

        for(unsigned int i = 0 ; i < this->mSize ; ++i)
        {
            this->mPtrInts[i] = rhs.mPtrInts[i];
        }
    }

    return *this;
}

int main()
{
    Foo fooA(string("Algorithm"), 0, 20);
    Foo fooB(string("Design Pattern"), 1, 40);

    fooA = fooB;
    fooA = fooA; // tried to copy iself. It should be prevented.

    return 0;
}
