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
        �񰡻� �Լ��� ������ �Ͽ���.
        �񰡻� �Լ��� static binding�� �̷�����Ƿ�,
        pointer�� data type�� �ش��ϴ� class�� method�� ȣ��ȴ�.
        ���� pointer�� ����Ű�� class�� �����ϴ�.
        ������ dynamic binding���� �������̴�.

        static  : compile������ ���/ȣ���� ���� �����Ѵ�.
        dynamic : running������ ���/ȣ���� ���� �����Ѵ�.
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
    ptrD->PrintAboutMe(); /// Derived*�� static binding�� �Ͼ.

    cout << "Base* : ";
    ptrB->PrintAboutMe(); /// Base*�� static binding�� �Ͼ.

    cout << "Base* [virtual]: ";
    ptrB->PrintAboutMe_Virtual(); /// virtual �Լ��̹Ƿ� dynamic binding�� �Ͼ.


    /// �׽�Ʈ �ڵ�
    PyramidMaker maker(60);
    maker.printPyramid_leftAligned();
    maker.printPyramid_rightAligned();
    maker.printPyramid_centerAligned();

    return 0;
}
