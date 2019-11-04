#include <iostream>
#include <string>
#include "Uncopyable.h"
#include <boost/noncopyable.hpp>

using namespace std;
using namespace boost;

class HouseForSale : private noncopyable
{

};

template<typename T>
class NamedObject
{
public:
    NamedObject(std::string& name, const T& value)
    : nameValue(name), objectValue(value)
    {}

private:
    std::string& nameValue;
    const T objectValue; // �� ������� ���� �⺻ �Ҵ� �����ڸ� ����� �� ����.
};

int main()
{
    cout << "Hello world!" << endl;

    std::string newDog("Persephone");
    std::string oldDog("Satch");

    NamedObject<int> p(newDog, 2);
    NamedObject<int> s(oldDog, 36);

    //p = s; // compile error : class���ο� const ��� ������ �����Ͽ� �⺻ �Ҵ� ������ ��� �Ұ�

    HouseForSale a;
    HouseForSale c;

    // ���� �����ڸ� ȣ���ϸ鼭 Uncopyable�� ��������ڵ� ȣ���Ϸ� ������
    // private�̱� ������ ȣ���� �Ұ����ϴ�. ������ �Ұ���.
    HouseForSale b(a);

    // ���Կ����ڸ� ȣ�������� private�Ӽ������� ȣ�� �Ұ�.
    c = a;

    return 0;
}
