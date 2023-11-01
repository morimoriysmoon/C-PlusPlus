#include <iostream>

using namespace std;

class PWindow
{
public :
    PWindow() : m_pnum(0) {}

    PWindow(const PWindow& rhs)
    {
        this->m_pnum = rhs.m_pnum;

        cout << "[PWindow(const PWindow& rhs)] called" << endl;
    }

    int getNum(void) { return m_pnum; }

    virtual void addNum(void)
    {
        ++m_pnum;

        cout << "[PWindow::addNum] number = " << m_pnum << endl;
    }

private:
    int m_pnum;
};


class CWindow : public PWindow
{
public:
    CWindow() : m_cnum(0) {}

    int getNum(void) { return m_cnum; }

    virtual void addNum(void)
    {


        /// 1> namespace를 통한 부모클래스의 함수 호출 : 가장 일반적인 방법.
        /// 본인도 이 방법을 사용했다.
        PWindow::addNum(); /// Ok



        /// 2> 부모의 포인터로 형변환을 시도했으나 virtual 함수로 인하여 본인의 것이 호출됨.
        ///static_cast<PWindow*>(this)->addNum(); /// 자식의 함수 호출. infinite loop로 인한 stack overflow.



        /// 3> 부모의 class로 형변환을 시도. 임시객체가 생성된다(복사 생성자를 통한)
        /**
            기본적으로 형변환은 "임시 객체를 만든다" 라고 알아 두기만 하면
            그럭저럭(... 이면 사수와 진지한 커피 한잔을 마실... )넘어갈 수 있고,
            splice는 S의 임시 객체 생성이므로 t의 T 부분이 잘려 나가는 문제점을 지적한다.
            책에는 생략된것으로 보아, ... 기초이기 때문이지 않을까.. 한다.

            기초란다.
            난 왜 몰랐지???
            부끄럽다.
        */
        static_cast<PWindow>(*this).addNum(); /// 임시객체(rvalue)의 함수를 호출하게 되므로 실제 값은 변경되지 않음.



        ++m_cnum;

        cout << "[PWindow] number = " << PWindow::getNum() << endl; /// "1"

        cout << "[CWindow::addNum] number = " << m_cnum << endl; /// "1"
    }

private:
    int m_cnum;
};


int main()
{
    cout << "Hello world!" << endl;

    PWindow* ptr_pwnd = new CWindow();

    ptr_pwnd->addNum();

    return 0;
}
