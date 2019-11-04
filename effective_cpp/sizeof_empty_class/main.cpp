#include <iostream>

using namespace std;

class Empty
{
};

class Dummy
{
public:
    Dummy(int _idx) : index(_idx) {}

    /**
        copy constructor�� �Ķ���Ͱ� Dummy rhs��� �����Ϸ��� �����Ѵ�.
        �ֳ��ϸ� �Ķ���Ͱ� ����Ǵ� �������� ���� �����ڰ� �ٽ� �Ҹ��� ������
		recursive function�� �Ǿ� stackoverflow�� �߻��Ѵ�.
        ���� const Dummy&�� ����ϴ� ���� �ƴϴ�.
    */
    Dummy(const Dummy& rhs)
    {
        this->index = rhs.index;
    }

    int getIndex(void) { return index; }

private:
    int index;
};


int main()
{
    cout << "Hello world!" << endl;

    /**
        �� class�� ������� 0�� �ƴ϶� 1�̴�. �����Ϸ��� 1����Ʈ char�� ���� �����Ѵ�.
        �ֳ��ϸ� �޸� ��򰡿��� ������ �����ؾ� ������ �����ϱ� ������.
    */
    cout << "The size of empty class is : " << sizeof(Empty) << endl;

    return 0;
}
