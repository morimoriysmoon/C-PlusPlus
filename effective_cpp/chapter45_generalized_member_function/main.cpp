#include <iostream>

using namespace std;

class Base
{
public:
    virtual ~Base() {}
};

class Derived : public Base
{
};

template<class U>
class Smart_Ptr
{
public:

    Smart_Ptr(void) : mPtr(nullptr) { }
    Smart_Ptr(U* _ptr) : mPtr(_ptr) { }
    Smart_Ptr(const Smart_Ptr<U>& rhs) : mPtr(rhs.get()) { }

    /**
        generalized copy constructor
        template<class T>의 경우, 멤버함수 template이므로 자동으로 deduction되어 추가할 필요가 없다.
    */
    template<class T>
    Smart_Ptr(const Smart_Ptr<T>& rhs) : mPtr(rhs.get())
    {
        cout << "template<class T> Smart_Ptr( const Smart_Ptr<T>& rhs) called." << endl;
    }

    /**
        Smart_Ptr<Base> 포인터에 compatible한 포인터를 대입하고 싶으면 아래의 대입(또는 할당)연산자를 정의해야 한다.
        template<class T>의 경우, 멤버함수 template이므로 자동으로 deduction되어 추가할 필요가 없다.
    */
    template<class T>
    Smart_Ptr<U>& operator=(const Smart_Ptr<T>& rhs)
    {
        cout << "operator=() called." << endl;
        this->mPtr = rhs.get();
        return *this;
    }

    U* get(void) const { return mPtr; }

private:
    U* mPtr;

};

int main()
{
    cout << "Hello world!" << endl;

    Smart_Ptr<Base> ptrCtor0;
    Smart_Ptr<Base> ptrCtor1(new Base());
    Smart_Ptr<Base> ptrCtor2(ptrCtor1);

    Smart_Ptr<Base> ptrBase0(new Base());
    Smart_Ptr<Base> ptrBase1(new Derived());

    Smart_Ptr<Derived> ptrDerived0(new Derived());
    //Smart_Ptr<Derived> ptrDerived1(new Base()); /** Derived* = Base* 는 불가 */

    ptrBase0 = ptrDerived0;

    Smart_Ptr<Base> ptrBase2(ptrDerived0);

    return 0;
}
