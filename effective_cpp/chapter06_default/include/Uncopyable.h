#ifndef UNCOPYABLE_H
#define UNCOPYABLE_H


class Uncopyable
{
    public:

    protected:
        Uncopyable() {}
        ~Uncopyable() {}

    private:
        Uncopyable(const Uncopyable&);
        Uncopyable& operator=(const Uncopyable&);
};

#endif // UNCOPYABLE_H
