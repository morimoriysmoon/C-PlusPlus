#include <iostream>
#include "rational.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    Rational_V1<int> onehalf(1,2);

    /**
        template 인자 추론 과정에서는 암시적 형식 변환이 고려되지 않는다.
        따라서 2가 Rational(2)로 암시적으로 변환될거라 기대하지 말아라.
    */

    Rational_V1<int> result0 = onehalf * 2; /** warning : unused variable */
    Rational_V1<int> result1(onehalf * 2); /** no warning */


    Rational_V2<int> onehalf_v2(1,2);
    Rational_V2<int> result2(onehalf_v2 * 2); /** no warning */

    return 0;
}
