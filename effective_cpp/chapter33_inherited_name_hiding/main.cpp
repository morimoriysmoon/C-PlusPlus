#include <iostream>
#include <string>

using namespace std;

/**
C++���� ����/�Լ� �˻��� ��Ģ (�̸��� �߿伺)

    ���� ���� >>>>>>>> ���� ����

    ���� �ڽ��� ���� �������� �̸��� ã�� ������ �������� ã�´�.
    (�ڽ��� ���� �������� �̸��� ã�Ҵٸ� �� �̻� ã�� �ʴ´�.)

    �� �� �˻� ������ �Լ�/������ �̸��̸�, �Լ��� ��� �Ű������� ������ �ʴ´�.
    �ڽ� Ŭ�������� �θ� Ŭ������ �����ϴ� �Լ�/������ ������ �̸��� ����� ���� �����ؾ� �Ѵ�.

    "�̸��� ���İ��� �ڴ� ���ѱ� ����� �����͸��� ����� ���� ���Դϴ�."


    public: ����̶� �ϸ�, Derived �� Base �̴ٸ� ���Ѵ�.
    �׷��Ƿ� Derived���� Base�� �͵��� �̸��� ������ ��ӹްڴٴ� ������ public: ��ӿ� ����ȴ�.
    ������ �ްڴٴ°� ��ü�� �̹� �ٸ� Ŭ������ ���ϱ� �����̴�.
    public: ����̶��, �� ����ؾ� �Ѵ�.

    ������ �λ��簡 �׷��� ������������ �ʴ�.
    �̸��� ������ �����ϰ��� �Ҷ��� �����ڵ�4���� ��Ÿ����ó�� private: �� ����Ͽ�, ���ȣ���� �ϸ� ������ �� �ʹ�.
    (�ּ��� �� �޾� �������� ������ �ִ°��� ���� �� �ʹ�..)
    ������ ��� ������ private: �̱� ������... �̷����� ����� ����.
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

class Derived : private Base /// private ����̴�.
{
public:

    /// �̸��� ã�� ������ Base���� ������ ȿ���� ������.
    using Base::mf1;

    virtual void mf1(void) /// forwarding function�̶� �Ҹ���.
    {
        Base::mf1(0); /// EC++ 244������. Link error �߻���.
    }
};

int main()
{
    cout << "Hello world!" << endl;

    Derived d;
    d.mf1();

    /**
        compile error : no matching function for call to 'Derived::mf1(int)'

        ��������� ������ ����, �Լ� mf1(int)�� �θ� Ŭ������ �����ϹǷ� �ƹ� ������ ����� �Ѵ�.
        ������ ������ ����.

        # ����
            1) mf1�̶�� �̸����� �ڽ��� �������������� �˻���.
            2) �ڽ��� �������� mf1(void)�� ������(�� �� �Ű������� Ȯ������ ����)�� Ȯ���Ѵ�.
            3) ����ڰ� ȣ���� �Լ��� mf1(void)�� �ƴ� mf1(int)��.
            4) mf1(int)�� �˻��� �Լ� ����Ʈ�� ����.
            5) �̷� ���� compile error �߻���.

        compile error�� ���ֱ� ���ؼ��� using Base::mf1; ����Ͽ� �̸��� ã�� ������ ���� �ش�(�ڽ��� �ܺα��� �˻��ϵ���).
    */
    d.mf1(1);

    /**
        compile error : inaccessible due to private inheritance

        ���⼭ ����:

            ��� �Լ��� ���� ����!
            ��� ������ ���� �Ұ���? ��????????
    */
    cout << "base name : " << d.name << endl;

    return 0;
}
