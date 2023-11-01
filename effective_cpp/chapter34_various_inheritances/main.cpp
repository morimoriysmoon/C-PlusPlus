#include <iostream>
#include <memory>
#include <vector>

using namespace std;

/*===============================================================*/

class Base
{
public:
    Base() {}
    virtual ~Base() {}

    /**
        부모 클래스에서 순수 가상 함수로 선언했기 때문에
        자식 클래스는 함수를 반드시 직접 구현해야 한다.(인터페이스 전달)

        또한, 구현부가 존재하므로 호출이 가능하다.(기본 동작 전달)

        선언부 : 인터페이스 전달
        구현부 : 기본 동작 전달


        #개념정리

        선언부/구현부를 분리할 수 있다.

        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        순수 가상 함수라고 하여 구현부가 없다는 의미는 아니다.
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        선언부를 순수 가상 함수로 규정함으로써
        자식 클래스에서 반드시 구현해야 함을 알리는 역할을 한다.
        이것이 중요한 점이다.
    */

    virtual void PrintAboutMe() const = 0;

};

void
Base::PrintAboutMe() const
{
    cout << endl << "Base::PrintAboutMe() called" << endl;
}

/*===============================================================*/

class Derived : public Base
{
public:

    /// 인터페이스이므로 반드시 구현해야 한다.
    virtual void PrintAboutMe() const;

};

void
Derived::PrintAboutMe() const
{
    cout << endl << "Derived::PrintAboutMe() called" << endl;
}


/*===============================================================*/

int main()
{
    unique_ptr<Derived> uPtr(new Derived);

    uPtr->PrintAboutMe();
    uPtr->Base::PrintAboutMe(); /** 부모 클래스의 함수를 명시적으로 호출하는 방법 */

    /** auto 기능을 확인하기 위한 테스트 코드
    */
    vector<int> nList;

    for(int i = 0 ; i < 1000 ; ++i)
    {
        nList.push_back(i*2);
    }

    auto it = nList.begin();

    for( ; it != nList.end() ; ++it)
    {
        cout << *it << endl;
    }

    return 0;
}
