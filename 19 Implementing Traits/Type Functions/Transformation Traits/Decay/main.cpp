#include <iostream>

template<typename T>
void f(T)
{

}

template<typename A>
void printParameterType(void (*)(A))
{
    std::cout <<"Parameter type: "<<typeid(A).name()<<'\n';
    std::cout << "- is int: "<<std::is_same<A,int>::value<<'\n';
    std::cout << "- is const: "<<std::is_const<A>::value<<'\n';
    std::cout<<'- is pointer: '<<std::is_pointer<A>::value<<'\n';
}

//DecayT
template<typename T>
struct DecayT : RemoveCVT<T>
{
    /* data */
};

template<typename T>
struct DecayT<T[]>
{
    using Type = T*;
};

template<typename T, std::size_t N>
struct DecayT<T[N]>
{
    using Type = T*;
};

template<typename R, typename... Args>
struct DecayT<R(Args...)>
{
    using Type = R (*)(Args...);
};

template<typename R, typename... Args>
struct DecayT<R(Args..., ...)>
{
    using Type = R (*)(Args..., ...);
};


template<typename T>
void printDecayedType()
{
    using A = typename DecayT<T>::Type;
    std::cout<<"Parameter type:"<<typeid(A).name()<<'\n';
    std::cout << "- is int: "<<std::is_same<A,int>::value<<'\n';
    std::cout << "- is const: "<<std::is_const<A>::value<<'\n';
    std::cout<<'- is pointer: '<<std::is_pointer<A>::value<<'\n';
}

template<typename T>
using Decay = typename DecayT<T>::type;

//C++11 support Std::decay<>

int main()
{
    printParameterType(&f<int>);
    printParameterType(&f<int const>);
    printParameterType(&f<int [7]>);
    printParameterType(&f<int(int)>);

    printDecayedType<int>();
    printDecayedType<int const>();
    printDecayedType<int [7]>();
    printDecayedType<int(int)>();

    return 1;
}