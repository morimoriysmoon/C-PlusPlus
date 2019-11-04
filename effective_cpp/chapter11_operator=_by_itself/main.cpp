#include <iostream>

using namespace std;


class Foo
{
public:
    Foo(const string& _name, const int _id, const unsigned long _arrsize);
    ~Foo();

    Foo& operator=(const Foo& rhs);

    /// �Ʒ� ���Կ����ڴ� �Ű������� �����ڰ� �ƴ϶�,
    /// ���� �����ڸ� ����� �纻�� �̿��ϰ� �ִ�.
    /// ��¼�� �����Ϸ��� �� ȿ������ �ڵ带 ����� �� ���� �ִ�.
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
    /// �Ź� �Ʒ��� ���ǹ��� �����ϴ� ���� ������ ���ڰ� ���� �� �ִ�.

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
