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

    // const / non-const�� overloading�� �����ϸ� ���� �ٸ� �Լ��� �ȴ�.
    // ���� : return value�� �������� ��Ұ� �� �� ����.

    const char& operator[](std::size_t position) const
    {
        return mText[position];
    }

    char& operator[](std::size_t position)
    {
        cout << "char& operator[]() called" << endl;
        // const�Լ��� ����Ͽ� non-const�Լ��� �����Ͽ���.�ڵ� �ߺ��� ���� ���Ͽ�.
        // static_cast<TextBook&>�� ����ϸ� ���ȣ���� �Ǿ� ������. ������ ������ �ʴ�.
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
    const TextBook ctb("const class"); // const class�� �����ؾ����� ��ü�� const�� �Լ��� ȣ���� �� �ִ�.

    tb[0] = 'N';
    //ctb[0] = 'C'; // error : assignment of read-only location

    return 0;
}
