#include <iostream>
#include <memory>
#include <utility>

using namespace std;

class Investment
{
public:
    enum
    {
            TYPE_AAA = 0,
            TYPE_BBB,
            TYPE_CCC,

            MAX_TYPE
    };

public:
    Investment() {}
    virtual ~Investment() { cout << "[dtor] Investment" << endl; }

    virtual int getType() { return MAX_TYPE; }
};

class AAAInvestment final: public Investment
{
public:
    ~AAAInvestment() { cout << "[dtor] AAAInvestment" << endl; }
    virtual int getType() { return TYPE_AAA; }
};

class BBBInvestment final: public Investment
{
public:
    ~BBBInvestment() { cout << "[dtor] BBBInvestment" << endl; }
    virtual int getType() { return TYPE_BBB; }
};

class CCCInvestment final: public Investment
{
public:
    ~CCCInvestment() { cout << "[dtor] CCCInvestment" << endl; }
    virtual int getType() { return TYPE_CCC; }
};

Investment * getInvestment(int _type)
{
    Investment * ptrInvestment = nullptr;

    switch(_type)
    {
    case Investment::TYPE_AAA:
        ptrInvestment = new AAAInvestment();
        break;

    case Investment::TYPE_BBB:
        ptrInvestment = new BBBInvestment();
        break;

    case Investment::TYPE_CCC:
        ptrInvestment = new CCCInvestment();
        break;

    default:
        break;
    }

    return ptrInvestment;
}

void dummyFunc(void)
{
    cout << "[Using classical way]" << endl;

    Investment* ptr = getInvestment(Investment::TYPE_AAA);

    /**

    이런 저런 동작을 수행한다.
    하지만, 예기치않게 함수가 강제로 종료될 수 있는데,
    이 경우, 아래의 delete문이 호출되지 않아 memory leak이 발생한다.
    이를 막기 위해서 별도의 class를 사용한다.

    */

    delete ptr;


    /** 첫번째 방법 : unique_ptr */
    cout << "[Using std::unique_ptr]" << endl;
    std::unique_ptr<Investment> uPtr(getInvestment(Investment::TYPE_AAA));
    //std::unique_ptr<Investment> uPtr_copied(uPtr); /// compile error : L-value cannot be used
    //std::unique_ptr<Investment> uPtr_copied = uPtr; /// compile error : L-value cannot be used

    /// std::move()의 역할 : 입력 파라미터를 R-value로 만들어 준다.
    /// http://en.cppreference.com/w/cpp/utility/move
    /// http://egloos.zum.com/frompt/v/2765424
    /// http://blog.mimu.me/understand-rvalue-reference-ko.html
    std::unique_ptr<Investment> uPtr_copied = std::move(uPtr);
    //cout << "[unique_ptr] Type: " << uPtr->getType() << endl; // terminated since uPtr moved to R-Value and not valid any more
    cout << "[unique_ptr] Type: " << uPtr_copied->getType() << endl;


    /** 두번째 방법 : auto_ptr */
    cout << "[Using std::auto_ptr]" << endl;
    std::auto_ptr<Investment> aPtr(getInvestment(Investment::TYPE_BBB)); // auto_ptr was deprecated
    std::auto_ptr<Investment> aPtr_copied = aPtr;
    //cout << "Type: " << aPtr->getType() << endl; // terminated since aPtr pointing to nullptr
    cout << "[auto_ptr] Type: " << aPtr_copied->getType() << endl;


    /** 세번째 방법 : shared_ptr */
    cout << "[Using std::shared_ptr]" << endl;
    std::shared_ptr<Investment> sPtr(getInvestment(Investment::TYPE_CCC));
    std::shared_ptr<Investment> sPtr_copied = sPtr;
    cout << "[shared_ptr] Type: " << sPtr->getType() << endl;
    cout << "[shared_ptr] Type: " << sPtr_copied->getType() << endl;

    /**
        위 세가지 방법의 공통점은 아래와 같다.

        1. 자원을 획득한 후에 자원 관리 객체에게 넘깁니다. (Resource Acquisition Is Initialization : RAII)
        2. 자원 관리 객체는 자신의 소멸자를 사용하여 자원이 확실히 해제되도록 합니다.
    */


    /** [사족] auto_ptr를 unique_ptr로 변경할 때 주의할 점 :

        auto_ptr은 operator=()를 사용할 수 있지만, (주의 : 원본 객체를 null로 만들어 버림)
        unique_ptr은 std::move()를 사용해야 한다.

        왜냐하면 서로 다른 2개의 unique_ptr가 하나의 객체를 가르킬 수는 없다.
        그래서 이름에 unique가 있다.

        http://stackoverflow.com/questions/3451099/stdauto-ptr-to-stdunique-ptr
    */
}

int main()
{
    cout << "Hello world!" << endl;

    dummyFunc();

    return 0;
}
