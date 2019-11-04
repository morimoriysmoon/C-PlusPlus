#include <iostream>
#include "rational.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    Rational_V1<int> onehalf(1,2);

    /**
        template ���� �߷� ���������� �Ͻ��� ���� ��ȯ�� ������� �ʴ´�.
        ���� 2�� Rational(2)�� �Ͻ������� ��ȯ�ɰŶ� ������� ���ƶ�.
    */

    Rational_V1<int> result0 = onehalf * 2; /** warning : unused variable */
    Rational_V1<int> result1(onehalf * 2); /** no warning */


    Rational_V2<int> onehalf_v2(1,2);
    Rational_V2<int> result2(onehalf_v2 * 2); /** no warning */

    return 0;
}
