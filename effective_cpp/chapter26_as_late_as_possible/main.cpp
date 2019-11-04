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
    ���� ���Ǹ� �ʹ� �ռ� �� �ʿ䰡 ����.
    ������ ������ �� �ִ�.
    if�� �Ʒ����� ������ �����ϴ� ���� ����.
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
    ���ǿ� ���ÿ� �ʱ�ȭ�Ѵ�.
    */
    string encrypted(password);

    /**
    ��ȣȭ �۾��� �����Ѵ�.
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
