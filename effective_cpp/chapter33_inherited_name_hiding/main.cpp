#include <iostream>
#include <string>

using namespace std;

/**
C++에서 변수/함수 검색의 규칙 (이름의 중요성)

    지역 변수 >>>>>>>> 전역 변수

    최초 자신의 지역 범위부터 이름을 찾고 없으면 전역에서 찾는다.
    (자신의 지역 범위에서 이름을 찾았다면 더 이상 찾지 않는다.)

    이 때 검색 기준은 함수/변수의 이름이며, 함수의 경우 매개변수는 보지도 않는다.
    자식 클래스에서 부모 클래스에 존재하는 함수/변수와 동일한 이름을 사용할 때는 주의해야 한다.

    "이름을 훔쳐가는 자는 빼앗긴 사람만 빈털터리로 만들고 마는 것입니다."


    public: 상속이라 하면, Derived 는 Base 이다를 뜻한다.
    그러므로 Derived에서 Base의 것들을 이름을 가려서 상속받겠다는 생각은 public: 상속에 위배된다.
    가려서 받겠다는것 자체가 이미 다른 클래스를 뜻하기 때문이다.
    public: 상속이라면, 다 상속해야 한다.

    하지만 인생사가 그렇게 간단하지만은 않다.
    이름을 가려서 구현하고자 할때는 예시코드4에서 나타낸것처럼 private: 로 상속하여, 명시호출을 하면 괜찮을 듯 싶다.
    (주석을 꼭 달아 가독성에 도움을 주는것이 좋을 듯 싶다..)
    하지만 멤버 변수도 private: 이기 때문에... 이런저런 고민이 많다.
*/

class Base
{
public:
    Base() : name("base name") {}
    virtual ~Base() {}

    virtual void mf1(void) = 0;
    virtual void mf1(int) { cout << "Base::mf1(int) called" << endl;}

public:
    string name;
};

class Derived : private Base /// private 상속이다.
{
public:

    /// 이름을 찾는 영역을 Base까지 넓히는 효과를 가진다.
    using Base::mf1;

    virtual void mf1(void) /// forwarding function이라 불린다.
    {
        Base::mf1(0); /// EC++ 244페이지. Link error 발생함.
    }
};

int main()
{
    cout << "Hello world!" << endl;

    Derived d;
    d.mf1();

    /**
        compile error : no matching function for call to 'Derived::mf1(int)'

        상식적으로 생각해 보면, 함수 mf1(int)는 부모 클래스에 존재하므로 아무 문제가 없어야 한다.
        하지만 에러가 난다.

        # 이유
            1) mf1이라는 이름으로 자신의 지역내에서부터 검색함.
            2) 자신의 지역내에 mf1(void)가 존재함(이 때 매개변수는 확인하지 않음)을 확인한다.
            3) 사용자가 호출한 함수는 mf1(void)가 아닌 mf1(int)임.
            4) mf1(int)는 검색한 함수 리스트에 없음.
            5) 이로 인해 compile error 발생함.

        compile error를 없애기 위해서는 using Base::mf1; 사용하여 이름을 찾는 영역을 넓혀 준다(자신의 외부까지 검색하도록).
    */
    d.mf1(1);

    /**
        compile error : inaccessible due to private inheritance

        여기서 질문:

            멤버 함수는 접근 가능!
            멤버 변수는 접근 불가능? 왜????????
    */
    cout << "base name : " << d.name << endl;

    return 0;
}
