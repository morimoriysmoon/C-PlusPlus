#ifndef _RATIONAL_H_
#define _RATIONAL_H_

template<typename T>
class Rational_V1
{
public:

    Rational_V1(const T& _num = 0, const T& _denom = 1)
    :num(_num), denom(_denom) { }

    const T numerator(void) const { return num; }
    const T denominator(void) const { return denom; }

    /**
        Ŭ���� ���ø������� ���� �Լ��� ����/�����Ͽ���.
        ����, template<T>�� ���ʿ��ϴ�.
    */
    friend
    const Rational_V1 operator*(const Rational_V1& lhs, const Rational_V1& rhs)
    {
        Rational_V1 value( lhs.numerator() * rhs.numerator() , lhs.denominator() * rhs.denominator() );
        return value;
    }

private:
    T num;
    T denom;
};

//template<typename T>
//const Rational_V1<T> operator*(const Rational_V1<T>& lhs, const Rational_V1<T>& rhs)
//{
//    Rational_V1<T> value( lhs.numerator() * rhs.numerator() , lhs.denominator() * rhs.denominator() );
//    return value;
//}

/**
    helper �Լ��� ����� ��
*/

/**
	���漱��
*/
template<typename T> class Rational_V2;

template<typename T>
const Rational_V2<T> doMultiply(const Rational_V2<T>& lhs, const Rational_V2<T>& rhs);

template<typename T>
class Rational_V2
{
public:

    Rational_V2(const T& _num = 0, const T& _denom = 1)
    :num(_num), denom(_denom) { }

    const T numerator(void) const { return num; }
    const T denominator(void) const { return denom; }

    /**
        Ŭ���� ���ø������� ���� �Լ��� ����/�����Ͽ���.
        ����, template<T>�� ���ʿ��ϴ�.
    */
    friend
    const Rational_V2 operator*(const Rational_V2& lhs, const Rational_V2& rhs)
    {
        /**
            helper�Լ��� ����Ͽ� �ڵ� ����� ���δ�.
        */
        return doMultiply(lhs, rhs);
    }

private:
    T num;
    T denom;
};

template<typename T>
const Rational_V2<T> doMultiply(const Rational_V2<T>& lhs, const Rational_V2<T>& rhs)
{
    Rational_V2<T> result( lhs.numerator() * rhs.numerator() , lhs.denominator() * rhs.denominator() );
    return result;
}

#endif // _RATIONAL_H_
