#include <iostream>
#include <utility>

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
        return decltype(isValidImpl<decltype(f),decltype(args)&&...>(nullptr)){};
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
auto isDefaultConstructible = isValid([](auto x) -> 
decltype((void)decltype(valueT(x))()){
});

//上诉定义的另外一种写法。
// auto isDefaultConstructible = [](auto&&... args)
// {
//     return decltype(isValidImpl<decltype([](auto x) -> 
//     decltype((void)decltype(valueT(x))())),decltype(args)&&...>(nullptr))
//     {

//     };
// };

template<typename T>
using IsDefaultConstructibleT = decltype(isDefaultConstructible(std::declval<T>()));

//However, once isValid is in place and understood, 
//many traits can be implementwith just one declaration
//example:
auto hasFirst = isValid([](auto x) -> decltype((void)valueT(x).first)
{
});


// int main()
// {
//     //for c++17
//     auto result = isDefaultConstructible(type<int>);   //true (int is default-constructible)
//     std::cout << "isDefaultConstructible(type<int>): " << result.value << '\n';
//     auto result1 = isDefaultConstructible(type<int&>);  //false (reference are not default-constructible)
//     std::cout << "isDefaultConstructible(type<int&>): " << result1.value << '\n';
//     return 1;
// }