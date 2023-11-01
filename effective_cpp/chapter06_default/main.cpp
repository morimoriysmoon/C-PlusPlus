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
    const T objectValue; // 이 멤버변수 덕에 기본 할당 연산자를 사용할 수 없다.
};

int main()
{
    cout << "Hello world!" << endl;

    std::string newDog("Persephone");
    std::string oldDog("Satch");

    NamedObject<int> p(newDog, 2);
    NamedObject<int> s(oldDog, 36);

    //p = s; // compile error : class내부에 const 멤버 변수가 존재하여 기본 할당 연산자 사용 불가

    HouseForSale a;
    HouseForSale c;

    // 복사 생성자를 호출하면서 Uncopyable의 복사생성자도 호출하려 하지만
    // private이기 때문에 호출이 불가능하다. 컴파일 불가능.
    HouseForSale b(a);

    // 대입연산자를 호출하지만 private속성때문에 호출 불가.
    c = a;

    return 0;
}
