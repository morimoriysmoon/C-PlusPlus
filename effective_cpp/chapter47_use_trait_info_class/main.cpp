#include <iostream>

using namespace std;

/**

    STL iterator�� ����


    =================================================================================


    1) �Է� �ݺ��� (input iterator)
        - ������ ����
        - �ѹ��� ��ĭ���� �̵�
        - �ڽ��� ����Ű�� ��ġ���� �� �ѹ� �б⸸ ����
        - �Է� ���Ͽ� ���� �б����� ���� �����͸� ���� ����
        > istream_iterator


    2) ��� �ݺ��� (outout iterator)
        - �Է� �ݺ��ڿ� ��������� ��¿� (�� �ѹ� ���⸸ ����)
        - ��� ���Ͽ� ���� ���� ���� ���� �����͸� ���� ����
        > ostream_iterator


    =================================================================================


    3) ������ �ݺ��� (forward iterator)
        - �Է� �ݺ��ڿ� ��� �ݺ��ڰ� �ϴ� ���� �⺻������ ��� ����
        - �ڽ��� ����Ű�� �ִ� ��ġ���� �б�� ���⸦ ���ÿ� ���� �� �� �� ����
        - "+=" ���� ������
        > ���� ���� ����Ʈ(slist)�� �����
        > TR1�� hash container�� �ݺ���


    4) ����� �ݺ��� (bidirectional iterator)
        - ������ �ݺ��ڿ� �ڷ� �� �� �ִ� ����� �߰�
        - "+=" ���� ������
        > STL�� list�� ���̴� �ݺ���
        > set, multiset, map, multimap



    =================================================================================


    5) ���� ���� �ݺ���
        - "+=" ���� ����
        - ����� �ݺ��ڿ� "�ݺ��� ��� ����" ���� ����� �߰�
        - �־��� �ݺ��ڸ� ������ �Ÿ���ŭ �յڷ� �̵���Ű�� ���� ��� �ð� �ȿ� �� �� ����
        > vector, deque, string


    =================================================================================


    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};



    �ݺ��ڸ� �־��� ȸ����ŭ �ݺ��ϸ� ���� �ð�(linear time)�� �ɸ�.
    ������ ���� ���� �ݺ��ڿ��� �� ����� ������.
    ���� ���� ���� �ݺ������� �Ǵ��Ͽ� ���� �ٸ� ���� ����� ����ϰ� �ʹ�.

    "Ư������(traits)" ��?
    ������ ���߿� � �־��� Ÿ���� ������ ��� �� �� �ְ� �ϴ� ��ü�� ��Ī�ϴ� ����.


    # �̹� �׸��� �ֿ� ����

    1) if���� run-time�߿� �Ǵܵ˴ϴ�. ������ compile-time�߿� �Ǵ��� �� �ֽ��ϴ�.
       overloading�� ����ϸ� �˴ϴ�.
        if( typeid(typename std::iterator_traits<IterT>::iterator_category)
                == typeis(std::random_access_iterator_tag) )
        {
        }


    2) �Ʒ�ó�� overloading �Լ����� �����. �׷� compile-time�� �����ȴ�.

        template<typename IterT, typename DistT>
        void doAdvance(IterT& iter, DistT d, std::randome_access_iterator_tag);
		
		template<typename IterT, typename DistT>
        void doAdvance(IterT& iter, DistT d, std::input_iterator_tag);
		
		template<typename IterT, typename DistT>
        void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag);


        void advance(IterT& iter, DistT d)
        {
            doAdvance(
                  iter, d,
                  typename std::iterator_traits<IterT>::iterator_category() // �� �κ����� ���ؼ� overloaded version ȣ��
                );
        }

    3) Ư������ Ŭ������ ������ ���߿� ����� �� �ִ� Ÿ�� ���� ������ ����� ���ϴ�.
        ���� Ư������ Ŭ������ ���ø� �� ���ø� Ư�� ������ ����Ͽ� �����մϴ�.

    4) �Լ� �����ε� ����� �����Ͽ� Ư������ Ŭ������ ����ϸ�, ������ Ÿ�ӿ� �����Ǵ�
        Ÿ�Ժ� if...else ���˹��� ������ �� �ֽ��ϴ�.



*/


/**
    �̹� �׸��� ��������.
*/


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
