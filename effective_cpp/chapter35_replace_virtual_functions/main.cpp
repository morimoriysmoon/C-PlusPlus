#include <iostream>
#include <functional>

using namespace std;

typedef std::function<int (int, int)> CalFunc;


/// global function
float FCalculator(int fir, int sec)
{
    return (fir*sec);
}

/// functor
class CCalculator
{
public:
    int operator()(int fir, int sec)
    {
        return (fir*sec);
    }
};

/// member method of a class
class CClassMethod
{
public:
    CClassMethod()
    {
        cout << "CClassMethod() called" << endl;
    }

    CClassMethod(const CClassMethod& rhs)
    {
        cout << "CClassMethod(const CClassMethod& rhs) called" << endl;
    }

    int calculator(int fir, int sec)
    {
        return (fir*sec);
    }
};

int main()
{
    cout << "Hello world!" << endl;


    /**====================================================================================*/
    CalFunc func0 = CCalculator();
    /// CalFunc func0(CCalculator()); /// compile error
    cout
            << "func0() : "
            << func0(4,3)
            << endl;


    /**====================================================================================*/
    CalFunc func1(&FCalculator);
    /// CalFunc func1(FCalculator); /// also possible
    cout
            << "func1() : "
            << func1(4,3) << endl;


    /**====================================================================================*/
    using namespace std::placeholders;

    CClassMethod method;
    CalFunc func2( std::bind(&CClassMethod::calculator, &method, _1, _2) );
    cout
            << "func2() : "
            << func2(4,3) << endl;


    /**====================================================================================*/
    auto func3 = std::bind(&CClassMethod::calculator, method, _1, _2);
    cout
            << "func3() : "
            << func3(4,3) << endl;

    return 0;
}
