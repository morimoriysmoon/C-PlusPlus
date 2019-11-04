#include <iostream>
#include <functional>

using namespace std;

class SimpleFunctor
{
public:
    SimpleFunctor()
    :fPtr0(&SimpleFunctor::dummyFunc), fPtr1(&SimpleFunctor::dummyFunc2)
    {}

    ~SimpleFunctor() {}

    void operator()(const int& rhs)
    {
        cout << "SimpleFunctor::operator() called : " << rhs << endl;
    }

    void CallFuncPtr(void)
    {
        (this->*fPtr0)();
        cout << "fPtr0 : " << fPtr0 << endl;

        (this->*fPtr1)();
        cout << "fPtr1 : " << fPtr1 << endl;
    }

private:
    typedef void(SimpleFunctor::* FuncPtr)(void);

    FuncPtr fPtr0;
    FuncPtr fPtr1;

    void dummyFunc(void)
    {
        cout << "dummyFunc()" << endl;
    }

    void dummyFunc2(void)
    {
        cout << "dummyFunc2()" << endl;
    }
};


template<typename T>
class DeleteThis
{
public:
    DeleteThis(int _id) : mId(_id) {}

    ~DeleteThis()
    {
        cout << "~DeleteThis() called" << endl;

        /// infinite loop로 인하여 stack overflow가 발생
        //delete this;
    }

    int getID(void) { return mId; }


/**


    ====================================================================================
    =============================== About "delete this;" ===============================
    ====================================================================================


    06/06/2014


    ================================================================================================

    http://stackoverflow.com/questions/3150942/c-delete-this


    1) neutral view

    As long as you're careful, it's OK for an object to commit suicide (delete this).

    Here's how I define "careful":

    You must be absolutely 100% positively sure that this object was allocated via new (not by new[], nor by placement new, nor a local object on the stack, nor a global, nor a member of another object; but by plain ordinary new).
    You must be absolutely 100% positively sure that your member function will be the last member function invoked on this object.
    You must be absolutely 100% positively sure that the rest of your member function (after the delete this line) doesn't touch any piece of this object (including calling any other member functions or touching any data members).
    You must be absolutely 100% positively sure that no one even touches the this pointer itself after the delete this line. In other words, you must not examine it, compare it with another pointer, compare it with NULL, print it, cast it, do anything with it.

    Naturally the usual caveats apply in cases where your this pointer is a pointer to a base class when you don't have a virtual destructor.


    2) negative view

    One of the reasons that C++ was designed was to make it easy to reuse code.
    In general, C++ should be written so that it works whether the class is instantiated on the heap, in an array, or on the stack.
    "Delete this" is a very bad coding practice because it will only work if a single instance is defined on the heap;
    and there had better not be another delete statement, which is typically used by most developers to clean up the heap.
    Doing this also assumes that no maintenance programmer in the future will cure a falsely perceived memory leak by adding a delete statement.

    Even if you know in advance that your current plan is to only allocate a single instance on the heap,
    what if some happy-go-lucky developer comes along in the future and decides to create an instance on the stack?
    Or, what if he cuts and pastes certain portions of the class to a new class that he intends to use on the stack?


    > 적절한 예제

    Well, in Component Object Model (COM) delete this construction can be a part of Release method that is called whenever you want to release aquisited object:

    void IMyInterface::Release()
    {
        --instanceCount;
        if(instanceCount == 0)
            delete this;
    }


    - 요약하면, delete this; 호출 후에 다른 동작을 하지 않는다면 문제가 없지만, 이 방법을 사용하기 꺼리는 사람도 적지 않다.



    ================================================================================================

    https://kldp.org/node/19565


    new, delete 에서는 위험하지만, 구현을 잘 생각하면 그런 트릭을 이용할 수 있습니다.

    member function의 개념은,

    1. 첫번째 인자를 "this" pointer로 넘겨 받는 함수.
    2. function mangling(decoration)에 class 이름이 들어가는 함수
    3. 컴파일 때, class 내부에 선언된 변수,함수에 접근가능한 함수.

    일 뿐입니다.


    멤버가 자기자신을 죽인다고 생각하지 않고, 첫번째 인자를 "다루고 있다" 정도로 생각하시면 됩니다.

    멤버 변수를 전혀 접근하지 않는 member함수가 있으면, null pointer에서도 실행이 됩니다.

    #include <stdio.h>

    class A
    {
            public:
            void test();
    };

    void A::test()
    {
            printf("Hi..");
    }

    int main()
    {
            A* a = 0;
            a->test();
            return 0;
    }

    보통 이런 경우에는 test를 static으로 만들어 주지요.

    static은 첫번째 인자로 this가 넘어가지 않는 함수입니다.

    delete도 마찬가지 입니다 첫번째 인자가 단지 this pointer인 함수라고 생각하시면됩니다.

*/

    void flushItself()
    {
        cout << "BEFORE : void flushItself()" << endl;

        functor(mId);
        delete this;

        cout << "AFTER : void flushItself()" << endl;
    }

private:
    int mId;
    T functor;
};


class Dog
{
public:
   Dog (int i) : tmp(i) {}
   virtual void bark ()
   {
      cout << "woof: " << tmp << endl;
   }
protected:
   int tmp;
};


class BullDog : public Dog
{
public:
    BullDog(int i) : Dog(i) {}

   virtual void bark ()
   {
      cout << "BullDog woof: " << tmp << endl;
   }
};

class LeapYearChecker
{
public:
    static bool IsLeapYear(unsigned long year)
    {
        bool bRet = false;
        int mod4 = year % 4;

        if(mod4 == 0)
        {
            bRet = true;
			
			int mod100 = year % 100;
			
            if(mod100 == 0)
            {
                bRet = false;
				
				int mod400 = year % 400;
				
                if(mod400 == 0)
                {
                    bRet = true;
                }
            }
        }
        return bRet;
    }
};

int main()
{
    cout << "Hello world!" << endl;



    DeleteThis<SimpleFunctor>* ptr = new DeleteThis<SimpleFunctor>(0);
    ptr->flushItself();

    /**
        gcc의 경우 "delete this" 후 멤버 변수에 접근을 하니 아무런 문제가 발생하지 않네요.
        그렇다고 안전한 코드라고 확신하기에는 무리가 있을 것 같습니다. 
		다른 컴파일러에서도 확인을 해볼 필요가 있을 것네요.
    */
    cout << "ID : " << ptr->getID() << endl;




    cout << "size of SimpleFunctor : " << sizeof(SimpleFunctor) << endl;




    SimpleFunctor Functor;
    cout << "1 : " << &Functor << endl;

    Functor.CallFuncPtr();

   Dog* pDog1 = new Dog (1);
   Dog* pDog2 = new BullDog (2);

   //BarkFunction pBark = &Dog::bark;
   std::function<void (Dog*)> f1 = &Dog::bark;

   f1(pDog1);
   f1(pDog2);


    cout << LeapYearChecker::IsLeapYear(2016) << endl;

    return 0;
}


/*****************************************************************************************************************



===================== 비정적 멤버함수 포인터와 일반 함수 포인터의 다른점 =====================

--------------------------------------------------------------------------------------
결론 : ANSI C++ 에서는 비정적 멤버 함수의 주소를 포인터 변수에 저장할수 없습니다.
--------------------------------------------------------------------------------------


32비트 시스템에서 일반 함수 와 클래스의 정적 멤버 함수는 4바이트 포인터 값하나로 표현가능합니다.

하지만 클래스의 비정적 멤버함수의 경우 "오브젝트주소 + 비정적 멤버 함수 주소" 형태가 되어야 정상적인 포인터 값으로서 의미가 있습니다.

비정적 멤버 함수내부에서 클래스 멤버 변수를 참조하는 코드는 항상 오브젝트의 주소를 알고 있어야 하기때문입니다.

따라서 다음과 같은 코드는

obj.funcA();

컴파일러가 funcA 멤버함수를 호출하기 위해 obj의 주소와 funcA 멤버함수의 주소 모두를 알고 있어야 호출가능합니다.

MyClass::funcA();

와 같은 함수호출코드는 컴파일러가 단순히 MyClass 네임스페이스의 funcA 함수 주소만 알고있어도 호출가능합니다.

따라서 ANSI C++ 에서는 비정적 멤버 함수의 주소를 포인터 변수에 저장할수 없습니다.

32비트 시스템에서 오브젝트 주소 + 함수 주소의 8바이트값을 4바이트 포인터 변수에 넣을수가 없기 때문입니다.

볼랜드 계열 (지금 이름은 엠바카데로) C++ 컴파일러는 이러한 경우를 대비하여 멤버함수 포인터 타입을 제공합니다.

지금 잘 기억이 안나는데 32비트 시스템에서 8바이트 크기를 가집니다. 그리고 당연히 해당 포인터로 멤버함수를 호출할 수 있습니다.

키워드가 지금 기억이 안나는데, 찾아보시면 금방 아실수 있을겁니다.

따라서 원하시는 작업은 볼랜드사의 C++ builder 에서는 쉽게 가능합니다.

MS 계열의 Visual C++ 에서는 일반적으로 할수 없고, 인라인 어셈블리 코드를 직접 작성하셔야 합니다.

Visual C++ 의 ATL 소스를 parkon 님이 원하시는 작업을 하기 위해 썽킹이라는 기술을 사용합니다.

인라인어셈블리를 사용한 트릭인데요. 코드 프로젝트의 atl 기초강좌(몇개 안됩니다)를 찾아보시면 잘 기술되어 있는 강좌를 찾아 보실수 있습니다.


================================================================

추가 내용 : 가상함수와 상속개념으로 인하여 실제로 쉽지 않다.

Suppose the function that Mehrdad wants the actual location of, happens to be a virtual function.

Then the base class implementation still has an entry point somewhere in the executable,

but a pointer-to-member for that function will not refer to that entry point,

because a call through it uses the virtual mechanism.

*/
