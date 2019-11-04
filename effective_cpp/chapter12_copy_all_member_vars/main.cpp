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
    : Base(_id), /// 기본클래스의 복사 생성자를 호출한다.
    index(_idx)
    {}

    Derived& operator=(const Derived& rhs)
    {
        /// 복사 대입 연산자를 직접 구현할 때는 주의해야 한다.
        /// 구현 내용이 확실히 잘못되었더라도 컴파일러는 입을 다물고 있다.


        /// 클래스의 복사 함수 2개를 구현할 때, 한쪽을 이용해서 다른 쪽을 구현하려는 시도는 절대로 하지 마세요.
        /// 그 대신, 공통된 동작을 제3의 함수에다 분리해 놓고 양쪽에서 이것을 호출하게 만들어서 해결합시다.


        /// 기본클래스도 반드시 복사해야 한다.
        /// const Derived& ==> const Base& : 포인터/참조자는 부모타입이 자식타입을 담을 수 있다.
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

    /// 포인터/참조자는 부모타입이 자식타입을 담을 수 있다.
    Base * ptr0 = new Derived(2,3);
    delete ptr0;

    /// 포인터/참조자는 부모타입이 자식타입을 담을 수 있다.
    Derived dC(2,3);
    Base& rC = dC;

    cout << "addType<int> : " << addType(1, 1) << endl;
    cout << "addType<float> : " << addType(1.5, 1.4) << endl;

    return 0;
}
