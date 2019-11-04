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

    �̷� ���� ������ �����Ѵ�.
    ������, ����ġ�ʰ� �Լ��� ������ ����� �� �ִµ�,
    �� ���, �Ʒ��� delete���� ȣ����� �ʾ� memory leak�� �߻��Ѵ�.
    �̸� ���� ���ؼ� ������ class�� ����Ѵ�.

    */

    delete ptr;


    /** ù��° ��� : unique_ptr */
    cout << "[Using std::unique_ptr]" << endl;
    std::unique_ptr<Investment> uPtr(getInvestment(Investment::TYPE_AAA));
    //std::unique_ptr<Investment> uPtr_copied(uPtr); /// compile error : L-value cannot be used
    //std::unique_ptr<Investment> uPtr_copied = uPtr; /// compile error : L-value cannot be used

    /// std::move()�� ���� : �Է� �Ķ���͸� R-value�� ����� �ش�.
    /// http://en.cppreference.com/w/cpp/utility/move
    /// http://egloos.zum.com/frompt/v/2765424
    /// http://blog.mimu.me/understand-rvalue-reference-ko.html
    std::unique_ptr<Investment> uPtr_copied = std::move(uPtr);
    //cout << "[unique_ptr] Type: " << uPtr->getType() << endl; // terminated since uPtr moved to R-Value and not valid any more
    cout << "[unique_ptr] Type: " << uPtr_copied->getType() << endl;


    /** �ι�° ��� : auto_ptr */
    cout << "[Using std::auto_ptr]" << endl;
    std::auto_ptr<Investment> aPtr(getInvestment(Investment::TYPE_BBB)); // auto_ptr was deprecated
    std::auto_ptr<Investment> aPtr_copied = aPtr;
    //cout << "Type: " << aPtr->getType() << endl; // terminated since aPtr pointing to nullptr
    cout << "[auto_ptr] Type: " << aPtr_copied->getType() << endl;


    /** ����° ��� : shared_ptr */
    cout << "[Using std::shared_ptr]" << endl;
    std::shared_ptr<Investment> sPtr(getInvestment(Investment::TYPE_CCC));
    std::shared_ptr<Investment> sPtr_copied = sPtr;
    cout << "[shared_ptr] Type: " << sPtr->getType() << endl;
    cout << "[shared_ptr] Type: " << sPtr_copied->getType() << endl;

    /**
        �� ������ ����� �������� �Ʒ��� ����.

        1. �ڿ��� ȹ���� �Ŀ� �ڿ� ���� ��ü���� �ѱ�ϴ�. (Resource Acquisition Is Initialization : RAII)
        2. �ڿ� ���� ��ü�� �ڽ��� �Ҹ��ڸ� ����Ͽ� �ڿ��� Ȯ���� �����ǵ��� �մϴ�.
    */


    /** [����] auto_ptr�� unique_ptr�� ������ �� ������ �� :

        auto_ptr�� operator=()�� ����� �� ������, (���� : ���� ��ü�� null�� ����� ����)
        unique_ptr�� std::move()�� ����ؾ� �Ѵ�.

        �ֳ��ϸ� ���� �ٸ� 2���� unique_ptr�� �ϳ��� ��ü�� ����ų ���� ����.
        �׷��� �̸��� unique�� �ִ�.

        http://stackoverflow.com/questions/3451099/stdauto-ptr-to-stdunique-ptr
    */
}

int main()
{
    cout << "Hello world!" << endl;

    dummyFunc();

    return 0;
}
