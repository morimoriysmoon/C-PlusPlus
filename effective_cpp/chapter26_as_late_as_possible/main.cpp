#include <iostream>
#include <string>
#include <stdexcept> /** logic_error */

using namespace std;

namespace EncryptDomain
{

const size_t MinimunPasswordLength = 8;

string encryptPassword_Bad(const string& password)
{
    /**
    변수 정의를 너무 앞서 할 필요가 없다.
    성능이 나빠질 수 있다.
    if문 아래에서 변수를 정의하는 것이 낫다.
    */
    string encrypted;

    if(password.size() < MinimunPasswordLength)
    {
        throw logic_error("Password is too short");
    }

    return encrypted;
}

string encryptPassword_Good(const string& password)
{
    if(password.size() < MinimunPasswordLength)
    {
        throw logic_error("Password is too short");
    }

    /**
    정의와 동시에 초기화한다.
    */
    string encrypted(password);

    /**
    암호화 작업을 수행한다.
    */

    return encrypted;
}

} // namespace EncryptDomain

int main()
{
    cout << "Hello world!" << endl;

    string rawPassword("qwertyuiop");

    EncryptDomain::encryptPassword_Bad(rawPassword);

    return 0;
}
