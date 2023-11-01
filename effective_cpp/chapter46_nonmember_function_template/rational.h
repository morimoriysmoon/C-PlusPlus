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
        클래스 템플릿내에서 비멤버 함수를 선언/정의하였다.
        따라서, template<T>는 불필요하다.
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
    helper 함수를 사용한 예
*/

/**
	전방선언
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
        클래스 템플릿내에서 비멤버 함수를 선언/정의하였다.
        따라서, template<T>는 불필요하다.
    */
    friend
    const Rational_V2 operator*(const Rational_V2& lhs, const Rational_V2& rhs)
    {
        /**
            helper함수를 사용하여 코드 사이즈를 줄인다.
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
