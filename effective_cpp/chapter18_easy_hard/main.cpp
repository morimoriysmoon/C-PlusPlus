#include <iostream>
#include <memory>
#include <string>

using namespace std;

class widget
{
public:
    widget(const string& _name)
    :mFlagCreate(false)
    ,mName(_name)
    {
        cout << "[ctor] widget" << endl;
    }

    ~widget()
    {
        cout << "[dtor] widget" << endl;
    }

    bool FlagCreate(void) { return mFlagCreate; }

    bool Create(void)
    {
        if(mFlagCreate) return false;

        cout << "[Create] widget" << endl;
        mFlagCreate = true;
        return true;
    }

    void Destroy(void)
    {
        if(mFlagCreate == false) return;

        cout << "[Destroy] widget" << endl;
        mFlagCreate = false;
    }

    const string& Name(void) { return mName; }

private:
    bool mFlagCreate;
    string mName;
};

class widgetDeleter
{
public:
    void operator() (widget *p) /// functor
    {
        cout << "call delete for widget object" << endl;
        if(p && p->FlagCreate())
        {
            cout << "the name of widget : " << p->Name() << endl;
            p->Destroy();
            delete p;
        }
    }
};

template<typename T>
class arrayDeleter
{
public:
    void operator()(T* ptrArr) /// functor
    {
        cout << "call delete for array object" << endl;
        delete [] ptrArr;
    }
};

int main()
{
    cout << "Hello world!" << endl;


    /**
		����ڰ� ���� �ۼ��� delete�Լ��� ���ø��� ������ �� �ִ�.
		������ ���, delete ȣ������ Destroy()�� ȣ���ؾ� �ϹǷ�, ������ delete�Լ���ü�� ����ϸ� �����ϴ�.
    */
    unique_ptr<widget, widgetDeleter> pWidget(new widget("unique ptr"));
    pWidget->Create();



    /**
        boost::shared_array��� std::unique_ptr�� ����ϸ� �ȴ�.
        �̷� �������� c++11�� shared_array�� �������� �ʴ´�.
    */

    const std::size_t nCount = 20;

    unique_ptr< int [], arrayDeleter<int> /* customized deleter */ > pArray (new int[nCount*nCount]);
    ///unique_ptr< int [] > pArray (new int[nCount*nCount]); // default deleter

    for(std::size_t i = 0 ; i < nCount ; ++i)
    {
        for(std::size_t j = 0 ; j < nCount ; ++j)
        {
            pArray[nCount*i + j] = 100*i + j;
            cout << pArray[nCount*i + j] << endl;
        }
    }

    return 0;
}
