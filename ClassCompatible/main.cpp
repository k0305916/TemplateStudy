#include <iostream>
#include <typeinfo>

class A
{
public:
    static void print()
    {
        std::cout <<"Call printA().\n";
    }

    static void test()
    {
        std::cout << "Call testA().\n";
    }
};

class B
{
public:
    static void printB()
    {
        std::cout << "Call printB().\n";
    }

    static void test()
    {
        std::cout << "Call testB().\n";
    }
};

template<typename T>
class CalgorithmBase
{
public:
    void test()
    {
        std::cout << "call test()\n";
        T::test();
    }
};



template<typename T>
class Calgorithm : public CalgorithmBase<T>
{
public:
    void print()
    {
        T::print();
        std::cout <<"Calgorithm Call print(): " << typeid(T).name() << '\n';
        CalgorithmBase<T>::test();
    }
};

template<>
class Calgorithm<B> : public CalgorithmBase<B>
{
public:
    void print()
    {
        B::printB();
        std::cout <<"Calgorithm Call print(): " << typeid(B).name() << '\n';
        CalgorithmBase<B>::test();
    }
};

//目的：使用一个模版，调用含有不同function的不同class；
int main()
{
    Calgorithm<A> objA;
    objA.print();

    Calgorithm<B> objB;
    objB.print();
    return 1;
}