#include <iostream>
#include <string>
#include <utility>
#include "19 Implementing Traits/SFINAE-Based Traits/Using Generic Lambdas for SFINAE/main.cpp"
using namespace std;

auto hasFirst1 = isValid([](auto&& x) -> 
decltype((void)&x.first){
});

template<typename T>
using HasFirstT = decltype(hasFirst1(std::declval<T>()));

auto hasSizeType = isValid([](auto&& x) -> 
typename std::decay_t<decltype(x)>::size_type{
});

template<typename T>
using HasSizeTypeT = decltype(hasSizeType(std::declval<T>()));

auto hasLess = isValid([](auto&& x, auto&& y) ->
decltype(x < y){
});

template<typename T1, typename T2>
using HasLessT = decltype(hasLess(std::declval<T1>(),std::declval<T2>()));

int main()
{
    cout << "first: " << HasFirstT<pair<int,int>>::value << '\n';   //true

    struct CX
    {
        using size_type = std::size_t;
    };
    cout <<"size_type(CX): " << HasSizeTypeT<CX>::value << '\n';        //true
    cout <<"size_type(int): " << HasSizeTypeT<int>::value << '\n';        //false

    cout << "HasLessT<int,char>::value: " << HasLessT<int,char>::value << '\n';     //true
    cout << "HasLessT<string,string>::value: " << HasLessT<string,string>::value << '\n';       //true
    cout << "HasLessT<string,int>::value: " << HasLessT<string,int>::value << '\n';             //false
    cout << "HasLessT<string,char*>::value: " << HasLessT<string,char*>::value << '\n';         //true
    return 1;
}