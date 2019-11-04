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
        �θ� Ŭ�������� ���� ���� �Լ��� �����߱� ������
        �ڽ� Ŭ������ �Լ��� �ݵ�� ���� �����ؾ� �Ѵ�.(�������̽� ����)

        ����, �����ΰ� �����ϹǷ� ȣ���� �����ϴ�.(�⺻ ���� ����)

        ����� : �������̽� ����
        ������ : �⺻ ���� ����


        #��������

        �����/�����θ� �и��� �� �ִ�.

        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ���� ���� �Լ���� �Ͽ� �����ΰ� ���ٴ� �ǹ̴� �ƴϴ�.
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        ����θ� ���� ���� �Լ��� ���������ν�
        �ڽ� Ŭ�������� �ݵ�� �����ؾ� ���� �˸��� ������ �Ѵ�.
        �̰��� �߿��� ���̴�.
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

    /// �������̽��̹Ƿ� �ݵ�� �����ؾ� �Ѵ�.
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
    uPtr->Base::PrintAboutMe(); /** �θ� Ŭ������ �Լ��� ��������� ȣ���ϴ� ��� */

    /** auto ����� Ȯ���ϱ� ���� �׽�Ʈ �ڵ�
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
