#include <iostream>

using namespace std;

class Base
{
public:
    Base(int _id) : id(_id) {}

    Base& operator=(const Base& rhs)
    {
        id = rhs.id;
        return *this;
    }

private:
    int id;
};

class Derived : public Base
{
public:
    Derived() : Base(0) {}
    Derived(int _id, int _idx)
    : Base(_id), /// �⺻Ŭ������ ���� �����ڸ� ȣ���Ѵ�.
    index(_idx)
    {}

    Derived& operator=(const Derived& rhs)
    {
        /// ���� ���� �����ڸ� ���� ������ ���� �����ؾ� �Ѵ�.
        /// ���� ������ Ȯ���� �߸��Ǿ����� �����Ϸ��� ���� �ٹ��� �ִ�.


        /// Ŭ������ ���� �Լ� 2���� ������ ��, ������ �̿��ؼ� �ٸ� ���� �����Ϸ��� �õ��� ����� ���� ������.
        /// �� ���, ����� ������ ��3�� �Լ����� �и��� ���� ���ʿ��� �̰��� ȣ���ϰ� ���� �ذ��սô�.


        /// �⺻Ŭ������ �ݵ�� �����ؾ� �Ѵ�.
        /// const Derived& ==> const Base& : ������/�����ڴ� �θ�Ÿ���� �ڽ�Ÿ���� ���� �� �ִ�.
        Base::operator=(rhs);
        this->index = rhs.index;
        return *this;
    }

    int getIndex(void) { return index; }

private:
    int index;
};

template<typename T>
T addType(const T para0, const T para1)
{
    return (para0 + para1);
}

int main()
{
    Derived dA(0,1);
    Derived dB(1,2);

    dB = dA;

    /// ������/�����ڴ� �θ�Ÿ���� �ڽ�Ÿ���� ���� �� �ִ�.
    Base * ptr0 = new Derived(2,3);
    delete ptr0;

    /// ������/�����ڴ� �θ�Ÿ���� �ڽ�Ÿ���� ���� �� �ִ�.
    Derived dC(2,3);
    Base& rC = dC;

    cout << "addType<int> : " << addType(1, 1) << endl;
    cout << "addType<float> : " << addType(1.5, 1.4) << endl;

    return 0;
}
