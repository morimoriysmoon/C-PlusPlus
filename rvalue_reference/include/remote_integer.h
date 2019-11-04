#ifndef REMOTE_INTEGER_H
#define REMOTE_INTEGER_H

#include <iostream>
#include <utility>

using namespace std;

#define __MOVABLE__

class remote_integer
{
    public:
        remote_integer() : m_ptr(nullptr)
        {
            cout << "default ctor called" << endl;
        }

        explicit remote_integer(const int n) : m_ptr(nullptr)
        {
            cout << "explicit unary ctor called" << endl;

            m_ptr = new int(n);
        }

        virtual ~remote_integer()
        {
            cout << "default dtor called" << endl;

            if(m_ptr) delete m_ptr;

            m_ptr = nullptr;
        }

        //////////////////////////////////////////////////////////////// copy
        /// copy ctor
        remote_integer(const remote_integer& other) : m_ptr(nullptr)
        {
            cout << "copy ctor called" << endl;

            *this = other;
        }

        /// copy asignment operator
        remote_integer& operator=(const remote_integer& other)
        {
            cout << "copy assignment operator called" << endl;

            if(this == &other) return *this;

            if(m_ptr) delete m_ptr;

            if(other.m_ptr)
            {
                m_ptr = new int(*other.m_ptr);
            }
            else
            {
                m_ptr = nullptr;
            }

            return *this;
        }

        int get() const
        {
            return m_ptr ? *m_ptr : 0;
        }

#ifdef __MOVABLE__

        //////////////////////////////////////////////////////////////// move
        /// rvalue ctor
        remote_integer(remote_integer&& other) : m_ptr(nullptr)
        {
            cout << "move ctor called" << endl;


            /// �Ű� ���� other�� �̸��� �����Ƿ� named rvalue�̰� �̰��� lvalue�� ó���ȴ�.
            /// ���� std::move()�� ����Ͽ� unnamed rvalue�� �����ؾ� move semantics�� ����� �� �ִ�.

            *this = std::move(other); /// move assignment op called
            //*this = other; /// copy assignment op called
        }

        /// rvalue assignment operator
        remote_integer& operator=(remote_integer&& other)
        {
            cout << "move assignment operator called" << endl;

            if(this == &other) return *this;

            if(this->m_ptr) delete this->m_ptr;

            this->m_ptr = nullptr;

            if(other.m_ptr)
            {
                this->m_ptr = other.m_ptr; /// stealing resource
                other.m_ptr = nullptr; /// stealing resource
            }

            return *this;
        }

#endif //__MOVABLE__

    protected:

    private:
        int* m_ptr;
};

#endif // REMOTE_INTEGER_H
