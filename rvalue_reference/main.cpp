#include <iostream>
#include <vector>
#include "remote_integer.h"

using namespace std;

string modifiable_rvalue() {
    return "cute";
}

const string const_rvalue() {
    return "fluffy";
}

void meow(string& s) {
    cout << "meow(string&): " << s << endl;
}

void meow(const string& s) {
    cout << "meow(const string&): " << s << endl;
}

void meow(string&& s) {
    cout << "meow(string&&): " << s << endl;
}

void meow(const string&& s) {
    cout << "meow(const string&&): " << s << endl;
}

string strange() {
    return "strange()";
}

const string charm() {
    return "charm()";
}


void test_various_ref()
{

    cout << endl << "~~~~~~~~~~~~~~~~~~~~[START] " << __FUNCTION__ << endl;

    string modifiable_lvalue("kittens");
    const string const_lvalue("hungry hungry zombies");

    string up("up");
    const string down("down");


    ///////////////////////////////////////////////// lvalue reference

    string& a = modifiable_lvalue;
    ///string& b = const_lvalue;
    ///string& c = modifiable_rvalue();
    ///string& d = const_rvalue();


    const string& e = modifiable_lvalue;
    const string& f = const_lvalue;
    const string& g = modifiable_rvalue();
    const string& h = const_rvalue();



    ///////////////////////////////////////////////// rvalue reference

    ///string&& i = modifiable_lvalue;
    ///string&& j = const_lvalue;
    string&& k = modifiable_rvalue();
    ///string&& l = const_rvalue();


    ///const string&& m = modifiable_lvalue;
    ///const string&& n = const_lvalue;
    const string&& o = modifiable_rvalue();
    const string&& p = const_rvalue();

////////////////////////////////////////////////////////////////////////////////////////////////

    meow(up);
    meow(down);
    meow(strange());
    meow(charm());

    cout << "~~~~~~~~~~~~~~~~~~~~[END] " << __FUNCTION__ << endl << endl;
}

remote_integer square(const remote_integer& r)
{
    const int i = r.get();

    return remote_integer(i * i);
}

remote_integer frumple(const int n)
{
    if (n == 1729)
    {
        return remote_integer(1729); /// 1) copy ctor 호출
    }

    remote_integer ret(n * n); /// 2) move ctor 호출

    /*
        1번과 2번의 차이가 무언지 모르겠음.
    */

    return ret;
}

void test_movable()
{
    cout << endl << "~~~~~~~~~~~~~~~~~~~~[START] " << __FUNCTION__ << endl;

    remote_integer a(8);

    cout << "a.get() : " << a.get() << endl;

    remote_integer b(10);

    cout << "[1st] b.get() : " << b.get() << endl;

    b = square(a); /// move assignment operator called

    cout << "[2nd] b.get() : " << b.get() << endl;

    remote_integer c = frumple(25); /// move ctor

    cout << "c.get() : " << c.get() << endl;

    remote_integer d = frumple(1729); /// copy ctor

    cout << "d.get() : " << d.get() << endl;

    cout << "~~~~~~~~~~~~~~~~~~~~[END] " << __FUNCTION__ << endl << endl;
}

void test_movable_2nd()
{
    cout << endl << "~~~~~~~~~~~~~~~~~~~~[START] " << __FUNCTION__ << endl;

    remote_integer x(frumple(5));

    cout << "x.get() : " << x.get() << endl;

    remote_integer y(frumple(1729));

    cout << "y.get() : " << y.get() << endl;

    cout << "~~~~~~~~~~~~~~~~~~~~[END] " << __FUNCTION__ << endl << endl;
}

void test_move_semantics_speed()
{
    std::vector<remote_integer> lst;

    for(size_t i = 0 ; i < 1 ; ++i)
    {
        lst.push_back(frumple(5));
    }
}

int main()
{
    //test_various_ref();

    //test_movable();

    //test_movable_2nd();

    //test_move_semantics_speed();

/** frumple(5); 내용 분석 : 비효율적이다.

    start

    explicit unary ctor called          <-- 함수내 로컬 lvalue변수 생성

    move ctor called                    <-- 리턴 값을 생성하는 과정
    move assignment operator called     <-- 리턴 값을 생성하는 과정

    default dtor called                 <-- 함수내 로컬 lvalue변수 소멸

    default dtor called                 <-- 함수가 리턴한 rvalue가 함수 외부에서 소멸 (rvalue는 single expression 외부에서 사라진다.)

    end

*/

    cout << "start" << endl;

    /// Return Value Optimization에 의해서 copy동작은 일어나 않고,
    /// compiler가 rvalue의 메모리 영역을 그대로 사용한다.
    remote_integer a = frumple(5);
    cout << "end" << endl;


/**  frumple(1729); 내용 분석 : 효율적이다.

    start

    explicit unary ctor called          <-- 함수내 로컬 rvalue변수 생성

    default dtor called                 <-- 함수가 리턴한 rvalue가 함수 외부에서 소멸 (rvalue는 single expression 외부에서 사라진다.)

    end

*/

    cout << "start" << endl;

    /// Return Value Optimization에 의해서 copy동작은 일어나 않고,
    /// compiler가 rvalue의 메모리 영역을 그대로 사용한다.
    remote_integer b = frumple(1729);
    cout << "end" << endl;

    return 0;
}
