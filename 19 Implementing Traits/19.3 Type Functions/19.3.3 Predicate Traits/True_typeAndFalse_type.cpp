#include <iostream>
template<bool val>
struct BoolConstant
{
    using Type = BoolConstant<val>;
    static constexpr bool value = val;
};

using TrueType = BoolConstant<true>;
using FalseType = BoolConstant<false>;

//can use IsSame to provide the same program.
template<typename T1, typename T2>
struct IsSameT : FalseType
{
    
};

template<typename T>
struct IsSameT<T,T> : TrueType
{

};

//以下也是变成技巧吧.---tag dispatching(this technique is called.)
template<typename T>
void fooImpl(T, TrueType)
{
    std::cout<<"fooImpl(T,true) for int called\n";
}

template<typename T>
void fooImpl(T,FalseType)
{
    std::cout<<"fooImpl(T,FalseType) for other type called.\n";
}

template<typename T>
void foo(T t)
{
    fooImpl(t,IsSameT<T,int>());                //choose imlp. depening on whether T is int
}

//expand:
template<typename T1, typename T2>
using IsSame = typename IsSameT<T1,T2>::Type;

//c++ provide: <type_traits>
//C++11 provide: std::true_type and std::false_type;
//in c++11 and c++14:
// namespace std
// {
//     using true_type = integral_constant<bool,true>;
//     using false_type = integral_constant<bool, false>;
// }
//in c++17:
// namespace std
// {
//     using true_type = bool_constant<true>;
//     using false_type = bool_constant<false>;
// }
// template<bool B>
// using bool_constant = integral_constant<bool,B>;


int main()
{
    foo(42);                        //calls fooImpl(42,TrueType)
    foo(7.7);                       //calls fooImpl(42,FalseType)

    IsSame<int,double> result;
    std::cout<<"IsSame<int,double>(): "<<result.value<<"\n";

    IsSame<int,int> result1;
    std::cout<<"IsSame<int,int>(): "<<result1.value<<"\n";
    return 1;
}