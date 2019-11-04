#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Based
{
public:
    Based(int _id, const string& _name)
    :id(_id)
    ,name(_name) {}

    virtual ~Based() {}

    virtual void doSomething() { cout << "Based do something..." << endl; }


    /** getter
    */
    int Id(void) { return id; }
    const string& Name(void) { return name; }

private:
    int id;
    string name;
};

class Derived : public Based
{
public:
    Derived(int _id, const string& _name, const string& _cmd)
    :Based(_id, _name)
    ,command(_cmd) {}

    ~Derived() {}

    virtual void doSomething() { cout << "Derived do something..." << endl; }

    /** getter
    */
    const string& Command(void) { return command; }

private:
    string command;
};

void UseBasedInsteadOfDerived(Based _base)
{
    /**
    �Ű������� Based�̹Ƿ� ���� ������ �Ű����� ���� BasedŸ���̴�.
    */

    cout << " ID : " << _base.Id() << endl;
    cout << " Name : " << _base.Name() << endl;

    _base.doSomething();

    // cout << " Command : " << endl;
}

void UseBasedPtrInsteadOfDerived(Based* _pbase)
{
    cout << " ID : " << _pbase->Id() << endl;
    cout << " Name : " << _pbase->Name() << endl;

    _pbase->doSomething();

    // cout << " Command : " << endl;
}

int main()
{
    Derived der(0, "derived", "ls -al");

    /**
    �Ű������� Based�̹Ƿ� ���� ������ �Ű����� ���� BasedŸ���̴�.
    �̷� �ൿ�� ���� �ϸ� �ȵȴ�.
    */
    UseBasedInsteadOfDerived(der);


    /** �����͸� ����ϸ� ��������.*/
    UseBasedPtrInsteadOfDerived(&der);

    return 0;
}
