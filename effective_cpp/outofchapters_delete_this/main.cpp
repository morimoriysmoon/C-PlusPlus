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

        /// infinite loop�� ���Ͽ� stack overflow�� �߻�
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


    > ������ ����

    Well, in Component Object Model (COM) delete this construction can be a part of Release method that is called whenever you want to release aquisited object:

    void IMyInterface::Release()
    {
        --instanceCount;
        if(instanceCount == 0)
            delete this;
    }


    - ����ϸ�, delete this; ȣ�� �Ŀ� �ٸ� ������ ���� �ʴ´ٸ� ������ ������, �� ����� ����ϱ� ������ ����� ���� �ʴ�.



    ================================================================================================

    https://kldp.org/node/19565


    new, delete ������ ����������, ������ �� �����ϸ� �׷� Ʈ���� �̿��� �� �ֽ��ϴ�.

    member function�� ������,

    1. ù��° ���ڸ� "this" pointer�� �Ѱ� �޴� �Լ�.
    2. function mangling(decoration)�� class �̸��� ���� �Լ�
    3. ������ ��, class ���ο� ����� ����,�Լ��� ���ٰ����� �Լ�.

    �� ���Դϴ�.


    ����� �ڱ��ڽ��� ���δٰ� �������� �ʰ�, ù��° ���ڸ� "�ٷ�� �ִ�" ������ �����Ͻø� �˴ϴ�.

    ��� ������ ���� �������� �ʴ� member�Լ��� ������, null pointer������ ������ �˴ϴ�.

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

    ���� �̷� ��쿡�� test�� static���� ����� ������.

    static�� ù��° ���ڷ� this�� �Ѿ�� �ʴ� �Լ��Դϴ�.

    delete�� �������� �Դϴ� ù��° ���ڰ� ���� this pointer�� �Լ���� �����Ͻø�˴ϴ�.

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
        gcc�� ��� "delete this" �� ��� ������ ������ �ϴ� �ƹ��� ������ �߻����� �ʳ׿�.
        �׷��ٰ� ������ �ڵ��� Ȯ���ϱ⿡�� ������ ���� �� �����ϴ�. 
		�ٸ� �����Ϸ������� Ȯ���� �غ� �ʿ䰡 ���� �ͳ׿�.
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



===================== ������ ����Լ� �����Ϳ� �Ϲ� �Լ� �������� �ٸ��� =====================

--------------------------------------------------------------------------------------
��� : ANSI C++ ������ ������ ��� �Լ��� �ּҸ� ������ ������ �����Ҽ� �����ϴ�.
--------------------------------------------------------------------------------------


32��Ʈ �ý��ۿ��� �Ϲ� �Լ� �� Ŭ������ ���� ��� �Լ��� 4����Ʈ ������ ���ϳ��� ǥ�������մϴ�.

������ Ŭ������ ������ ����Լ��� ��� "������Ʈ�ּ� + ������ ��� �Լ� �ּ�" ���°� �Ǿ�� �������� ������ �����μ� �ǹ̰� �ֽ��ϴ�.

������ ��� �Լ����ο��� Ŭ���� ��� ������ �����ϴ� �ڵ�� �׻� ������Ʈ�� �ּҸ� �˰� �־�� �ϱ⶧���Դϴ�.

���� ������ ���� �ڵ��

obj.funcA();

�����Ϸ��� funcA ����Լ��� ȣ���ϱ� ���� obj�� �ּҿ� funcA ����Լ��� �ּ� ��θ� �˰� �־�� ȣ�Ⱑ���մϴ�.

MyClass::funcA();

�� ���� �Լ�ȣ���ڵ�� �����Ϸ��� �ܼ��� MyClass ���ӽ����̽��� funcA �Լ� �ּҸ� �˰��־ ȣ�Ⱑ���մϴ�.

���� ANSI C++ ������ ������ ��� �Լ��� �ּҸ� ������ ������ �����Ҽ� �����ϴ�.

32��Ʈ �ý��ۿ��� ������Ʈ �ּ� + �Լ� �ּ��� 8����Ʈ���� 4����Ʈ ������ ������ �������� ���� �����Դϴ�.

������ �迭 (���� �̸��� ����ī����) C++ �����Ϸ��� �̷��� ��츦 ����Ͽ� ����Լ� ������ Ÿ���� �����մϴ�.

���� �� ����� �ȳ��µ� 32��Ʈ �ý��ۿ��� 8����Ʈ ũ�⸦ �����ϴ�. �׸��� �翬�� �ش� �����ͷ� ����Լ��� ȣ���� �� �ֽ��ϴ�.

Ű���尡 ���� ����� �ȳ��µ�, ã�ƺ��ø� �ݹ� �ƽǼ� �����̴ϴ�.

���� ���Ͻô� �۾��� ��������� C++ builder ������ ���� �����մϴ�.

MS �迭�� Visual C++ ������ �Ϲ������� �Ҽ� ����, �ζ��� ����� �ڵ带 ���� �ۼ��ϼž� �մϴ�.

Visual C++ �� ATL �ҽ��� parkon ���� ���Ͻô� �۾��� �ϱ� ���� ��ŷ�̶�� ����� ����մϴ�.

�ζ��ξ������ ����� Ʈ���ε���. �ڵ� ������Ʈ�� atl ���ʰ���(� �ȵ˴ϴ�)�� ã�ƺ��ø� �� ����Ǿ� �ִ� ���¸� ã�� ���Ǽ� �ֽ��ϴ�.


================================================================

�߰� ���� : �����Լ��� ��Ӱ������� ���Ͽ� ������ ���� �ʴ�.

Suppose the function that Mehrdad wants the actual location of, happens to be a virtual function.

Then the base class implementation still has an entry point somewhere in the executable,

but a pointer-to-member for that function will not refer to that entry point,

because a call through it uses the virtual mechanism.

*/
