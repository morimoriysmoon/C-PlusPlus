#include <iostream>

using namespace std;

/*===================================================*/

class Base
{
public:

    void PrintAboutMe();

    virtual void PrintAboutMe_Virtual();
};

void
Base::PrintAboutMe()
{
    cout << "Base::PrintAboutMe() called" << endl;
}

void
Base::PrintAboutMe_Virtual()
{
    cout << "Base::PrintAboutMe_Virtual() called" << endl;
}

/*===================================================*/

class Derived : public Base
{
public:

    /**
        비가상 함수를 재정의 하였다.
        비가상 함수는 static binding이 이루어지므로,
        pointer의 data type에 해당하는 class의 method가 호출된다.
        실제 pointer가 가르키는 class와 무관하다.
        이점이 dynamic binding과의 차이점이다.

        static  : compile시점에 사용/호출할 것을 결정한다.
        dynamic : running시점에 사용/호출할 것을 결정한다.
    */

    void PrintAboutMe();

    virtual void PrintAboutMe_Virtual();
};

void
Derived::PrintAboutMe()
{
    cout << "Derived::PrintAboutMe() called" << endl;
}

void
Derived::PrintAboutMe_Virtual()
{
    cout << "Derived::PrintAboutMe_Virtual() called" << endl;
}
/*===================================================*/

#include <string>

class PyramidMaker
{
public:
    PyramidMaker(const int _level)
    : m_level(_level)
    {}
    virtual ~PyramidMaker() {}

    void printPyramid_leftAligned()
    {
        std::string output;

        for(int i = 1 ; i <= m_level ; ++i)
        {
            for(int j = 0 ; j < i ; ++j)
            {
                output.append("@");
            }
            output.append("\n");
        }

        std::cout << output << std::endl;
    }

    void printPyramid_centerAligned()
    {
        std::string output;

        for(int i = 1 ; i <= m_level ; ++i)
        {
            /// add space
            int amountSpace = m_level - i;
            for(int space = 0 ; space < amountSpace ; ++space)
            {
                output.append(" ");
            }

            /// add star
            int amountStar = 2*i -1;
            for(int star = 0 ; star < amountStar ; ++star)
            {
                output.append("@");
            }

            output.append("\n");
        }

        std::cout << output << std::endl;
    }

    void printPyramid_rightAligned()
    {
        std::string output;

        for(int i = 1 ; i <= m_level ; ++i)
        {
            /// add space
            int amountSpace = m_level - i;
            for(int space = 0 ; space < amountSpace ; ++space)
            {
                output.append(" ");
            }

            /// add star
            int amountStar = i;
            for(int star = 0 ; star < amountStar ; ++star)
            {
                output.append("@");
            }

            output.append("\n");
        }

        std::cout << output << std::endl;
    }

private:
    int m_level;

};

/*===================================================*/

int main()
{
    cout << "Hello world!" << endl;

    Derived x;

    Derived* ptrD = &x;
    Base* ptrB = &x;

    cout << "Derived* : " ;
    ptrD->PrintAboutMe(); /// Derived*에 static binding이 일어남.

    cout << "Base* : ";
    ptrB->PrintAboutMe(); /// Base*에 static binding이 일어남.

    cout << "Base* [virtual]: ";
    ptrB->PrintAboutMe_Virtual(); /// virtual 함수이므로 dynamic binding이 일어남.


    /// 테스트 코드
    PyramidMaker maker(60);
    maker.printPyramid_leftAligned();
    maker.printPyramid_rightAligned();
    maker.printPyramid_centerAligned();

    return 0;
}
