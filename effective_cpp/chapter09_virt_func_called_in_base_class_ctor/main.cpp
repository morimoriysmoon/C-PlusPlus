#include <iostream>

using namespace std;


class Transaction
{
public:
    Transaction()
    {
        /// 1)
        /// 자식의 LogTransaction()가 불릴거라 생각하면 안된다.
        /// 왜냐하면 아직 자식은 초기화도 되지 않았다.
        //LogTransaction();

        /// 2)
        /// 아래처럼 별도의 함수를 사용하면 빌드에는 문제가 없지만
        /// 실행하면 "pure virtual function called"로 인해 사망함.
        /// 훨씬 더 사악한 코드임.
        doInitialize();
    }

    virtual ~Transaction() {}

    virtual void LogTransaction(void) const = 0;

private:
    void doInitialize(void)
    {
        LogTransaction();
    }
};


class BuyTransaction :public Transaction
{
public:
    BuyTransaction()
    {
        LogTransaction();
    }

    ~BuyTransaction() {}

    virtual void LogTransaction(void) const
    {
        cout << "BuyTransaction::LogTransaction called" << endl;
    }
};

/**

    생성          Base                : Derive는 없다고 생각
                        \
                        Derive

                            |
                            | 이런 저런 동작을 수행한다.
                            |

     소멸               ~Derive
                        /
                    ~Base             : Derive는 없다고 생각
*/




int main()
{
    BuyTransaction bt; // terminate called : pure virtual method called
    return 0;
}
