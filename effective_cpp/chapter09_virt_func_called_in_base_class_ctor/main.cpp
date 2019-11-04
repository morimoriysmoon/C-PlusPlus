#include <iostream>

using namespace std;


class Transaction
{
public:
    Transaction()
    {
        /// 1)
        /// �ڽ��� LogTransaction()�� �Ҹ��Ŷ� �����ϸ� �ȵȴ�.
        /// �ֳ��ϸ� ���� �ڽ��� �ʱ�ȭ�� ���� �ʾҴ�.
        //LogTransaction();

        /// 2)
        /// �Ʒ�ó�� ������ �Լ��� ����ϸ� ���忡�� ������ ������
        /// �����ϸ� "pure virtual function called"�� ���� �����.
        /// �ξ� �� ����� �ڵ���.
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

    ����          Base                : Derive�� ���ٰ� ����
                        \
                        Derive

                            |
                            | �̷� ���� ������ �����Ѵ�.
                            |

     �Ҹ�               ~Derive
                        /
                    ~Base             : Derive�� ���ٰ� ����
*/




int main()
{
    BuyTransaction bt; // terminate called : pure virtual method called
    return 0;
}
