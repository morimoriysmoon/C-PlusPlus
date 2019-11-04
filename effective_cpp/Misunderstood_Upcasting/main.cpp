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


        /// 1> namespace�� ���� �θ�Ŭ������ �Լ� ȣ�� : ���� �Ϲ����� ���.
        /// ���ε� �� ����� ����ߴ�.
        PWindow::addNum(); /// Ok



        /// 2> �θ��� �����ͷ� ����ȯ�� �õ������� virtual �Լ��� ���Ͽ� ������ ���� ȣ���.
        ///static_cast<PWindow*>(this)->addNum(); /// �ڽ��� �Լ� ȣ��. infinite loop�� ���� stack overflow.



        /// 3> �θ��� class�� ����ȯ�� �õ�. �ӽð�ü�� �����ȴ�(���� �����ڸ� ����)
        /**
            �⺻������ ����ȯ�� "�ӽ� ��ü�� �����" ��� �˾� �α⸸ �ϸ�
            �׷�����(... �̸� ����� ������ Ŀ�� ������ ����... )�Ѿ �� �ְ�,
            splice�� S�� �ӽ� ��ü �����̹Ƿ� t�� T �κ��� �߷� ������ �������� �����Ѵ�.
            å���� �����Ȱ����� ����, ... �����̱� �������� ������.. �Ѵ�.

            ���ʶ���.
            �� �� ������???
            �β�����.
        */
        static_cast<PWindow>(*this).addNum(); /// �ӽð�ü(rvalue)�� �Լ��� ȣ���ϰ� �ǹǷ� ���� ���� ������� ����.



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
