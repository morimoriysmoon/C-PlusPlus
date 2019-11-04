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
		사용자가 직접 작성한 delete함수를 템플릿에 지정할 수 있다.
		위젯의 경우, delete 호출전에 Destroy()를 호출해야 하므로, 별도의 delete함수객체를 사용하면 유용하다.
    */
    unique_ptr<widget, widgetDeleter> pWidget(new widget("unique ptr"));
    pWidget->Create();



    /**
        boost::shared_array대신 std::unique_ptr를 사용하면 된다.
        이런 이유에서 c++11은 shared_array를 지원하지 않는다.
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
