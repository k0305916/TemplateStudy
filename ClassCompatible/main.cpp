#include <iostream>
#include <typeinfo>

class A
{
public:
    void print()
    {
        std::cout <<"Call printA().\n";
    }

    void test()
    {
        std::cout << "Call testA().\n";
    }
};

class B
{
public:
    void printB()
    {
        std::cout << "Call printB().\n";
    }

    void test()
    {
        std::cout << "Call testB().\n";
    }
};

template<typename T>
class CalgorithmBase
{
public:
    CalgorithmBase(){};
    virtual ~CalgorithmBase(){};

    void Func(T t)
    {
        std::cout << "call Base Func()\n";
        this->print(t);
        test(t);
    }

private:

    virtual void print(T t)
    {
    }

    void test(T t)
    {
        std::cout << "call test()\n";
        t.test();
    }
};



template<typename T>
class Calgorithm : public CalgorithmBase<T>
{
public:
    Calgorithm(){};
    virtual ~Calgorithm(){};

private:
    virtual void print(T t) override
    {
        t.print();
        std::cout <<"Calgorithm Call print(): " << typeid(T).name() << '\n';
    }
};

template<>
class Calgorithm<B> : public CalgorithmBase<B>
{
public:
    Calgorithm(){};
    virtual ~Calgorithm(){};

private:
    virtual void print(B t) override
    {
        t.printB();
        std::cout <<"Calgorithm Call print(): " << typeid(B).name() << '\n';
    }
};

//目的：使用一个模版，调用含有不同function的不同class；
int main()
{
    Calgorithm<A> objA;
    A a;
    objA.Func(a);

    Calgorithm<B> objB;
    B b;
    objB.Func(b);
    return 1;
}