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
    매개변수가 Based이므로 복사 생성된 매개변수 역시 Based타입이다.
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
    매개변수가 Based이므로 복사 생성된 매개변수 역시 Based타입이다.
    이런 행동은 절대 하면 안된다.
    */
    UseBasedInsteadOfDerived(der);


    /** 포인터를 사용하면 문제없다.*/
    UseBasedPtrInsteadOfDerived(&der);

    return 0;
}
