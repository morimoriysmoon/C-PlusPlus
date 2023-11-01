#include <iostream>
#include <string>

using namespace std;

class TextBook
{

public:
    TextBook(const char* __Str)
    :mText(__Str)
    ,mValue(0)
    ,mId(0)
    {
    }

    // const / non-const도 overloading이 가능하며 서로 다른 함수가 된다.
    // 주의 : return value는 다형성의 요소가 될 수 없다.

    const char& operator[](std::size_t position) const
    {
        return mText[position];
    }

    char& operator[](std::size_t position)
    {
        cout << "char& operator[]() called" << endl;
        // const함수를 사용하여 non-const함수를 구현하였다.코드 중복를 막기 위하여.
        // static_cast<TextBook&>를 사용하면 재귀호출이 되어 버린다. 영원히 끝나지 않는.
        return const_cast<char&>( static_cast<const TextBook&>(*this)[position] );
    }

private:
    string mText;

    int mValue;
    int mId;
};


int main()
{
    cout << "Hello world!" << endl;

    TextBook tb("non const class");
    const TextBook ctb("const class"); // const class를 정의해야지만 몸체가 const인 함수를 호출할 수 있다.

    tb[0] = 'N';
    //ctb[0] = 'C'; // error : assignment of read-only location

    return 0;
}
