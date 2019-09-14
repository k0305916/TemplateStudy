#include <iostream>
#include <type_traits>          //defines true_type and false_type
#include <utility>              // for c++17 example
#include "19 Implementing Traits/Predicate Traits/IsSameT.cpp"

struct NoDefaultConstruct
{
    NoDefaultConstruct() = delete;
};


/*
explain:
  we define the general case to be derived form std::false_type,because
  by default a type doesnot have the member size_type.

  The interesting feature here is the second template argument that defaults to 
  the type of a helper VoidT. It enables us to provide parial specializations that
  use an arbitrary number of compile-time type constructs.

  In this case, we need only one construct: decltype(T()) to check again 
  whether the default constructor for T is valid.
*/

//helper to ignore any number of template parameters:
template<typename...>
using VoidT = void;

//primary template
template<typename, typename = VoidT<>>
struct IsDefaultConstructibleT : std::false_type
{
};

//partial specialization(may be SFINAE'd away):
template<typename T>
struct IsDefaultConstructibleT<T,VoidT<decltype(T())>> : std::true_type
{
};

//In C++17, the c++ standard library introduced a type trait std::void_t<> that 
//corresponds to the type VoidT introduced here.

//helper: checking validity of f(args...) for F f and Args... args:
template<typename F, typename... Args, 
typename = decltype(std::declval<F>()(std::declval<Args&&>() ...))>     // 这一行是啥意思？
std::true_type isValidImpl(void*);

//fallback if helper SFINAE'd out:
template<typename F, typename... Args>
std::false_type isValidImpl(...);

//define a lambda that takes a lambda f and returns whether calling f with args is valid
constexpr auto isValid = [](auto f)
{
    return [](auto&&... args)       //lambda还能这样写？晕，第一次看到。。。
    {                  
        return decltype(isValidImpl<decltype(f),decltype(args)>(nullptr)){};
        // return "";
    };
};

//helper template to represent a type as a value
template<typename T>
struct TypeT
{
    using Type = T;
};

//helper to wrap a type as a value
template<typename T>
constexpr auto type = TypeT<T>{};

//helper to unwrap a wrapped type in unevaluated contexts
template<typename T>
T valueT(TypeT<T>);             // no definition needed


//isValid is a traits factory: A component that generates traits 
//checking objects from its argument.
constexpr auto isDefaultConstructible = isValid(
    [](auto x) -> decltype((void)decltype(valueT(x))())
    {

    });

constexpr auto isDefaultConstructible = [](auto&&... args)
{
    return decltype(isValidImpl<decltype([](auto x) -> 
    decltype((void)decltype(valueT(x))())),decltype(args)&&...>(nullptr))
    {

    };
}

template<typename T>
using IsDefaultConstructibleT = decltype(isDefaultConstructible(std::declval<T>()));

//However, once isValid is in place and understood, 
//many traits can be implementwith just one declaration
//example:
constexpr auto hasFirst = isValid([](auto x) -> decltype((void)valueT(x).first)
{
});


int main()
{
    IsDefaultConstructibleT<NoDefaultConstruct> a;          //false_type
    IsDefaultConstructibleT<int> b;                         //true_type

    //for c++17
    isDefaultConstructible(type<int>);   //true (int is default-constructible)
    isDefaultConstructible(type<int&>);  //false (reference are not default-constructible)
    return 1;
}