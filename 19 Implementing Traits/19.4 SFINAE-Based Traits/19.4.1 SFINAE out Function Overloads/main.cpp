#include <iostream>
#include <typeinfo>
#include "19 Implementing Traits/Predicate Traits/IsSameT.cpp"

//This allows us to write traits that determine whether a type has a specific member,
// supports a specific operation, or is a class.

//The two main approaches for SFINAE-Based traits are 
//1. to SFINAE out functions overloads;
//2. SFINAE out partial specializations.

//using SFINAE with function overloading to find out 
//whether a type is a default constructible, so that you can 
//create objects without any value for initialization.

//The usual approach to implement a SFINAE-base trait with function overloading is 
//to declare two overloaded function templates names test() with different return types:
template<typename T>
struct IsDefaultConstructibleT
{
public:
    //test() trying substitute call of a default constructor for T passed as U:
    template<typename U, typename = decltype(U())>
    static char test(void*);

    //test() fallback:
    template<typename>
    static long test(...);
public:
    static constexpr bool value = IsSameT<decltype(test<T>(nullptr)),char>::value;
};

template<typename T>
template<typename U, typename>
char IsDefaultConstructibleT<T>::test(void* obj)
{
    std::cout << "call: char IsDefaultConstructibleT<T>::test(void*)\n";
}

template<typename T>
template<typename>
long IsDefaultConstructibleT<T>::test(...)
{
    std::cout << "call: long IsDefaultConstructibleT<T>test(...)\n";
}

struct NoDefault {
    NoDefault() = delete;
    //NoDefault(const NoDefault &d) {};     //与下面的好像是一样的。。。。
    NoDefault(const NoDefault &d) = default;
};



int main()
{
    auto a = IsDefaultConstructibleT<int>::value;       //return 1
    std::cout << a <<'\n';
    IsDefaultConstructibleT<int> aa;
    aa.test<int>((void*)&a);
    auto b = IsDefaultConstructibleT<NoDefault>::value; //return 0
    std::cout << b <<'\n';
    IsDefaultConstructibleT<NoDefault> bb;
    bb.test<NoDefault>(b);                                 //call test(...).
    bb.test<NoDefault>((void*)&b);                         //call test(...).
    
    return 1;
}