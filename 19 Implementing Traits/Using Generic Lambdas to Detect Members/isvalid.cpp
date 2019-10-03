#include <iostream>
#include <string>
#include <utility>
#include "19 Implementing Traits/SFINAE-Based Traits/Using Generic Lambdas for SFINAE/main.cpp"
using namespace std;

/*
The following example illustrates how to define traits checking whether 
a data or type member such as first or size_type exists or 
whether operator< is defined for two objects of different types.
*/

int main()
{
    cout << boolalpha;
    //define to check for data member first:
    auto hasFirst = isValid([](auto x) -> 
    decltype((void)valueT(x).first){
    });

    cout << "hasFirst: " << hasFirst(type<pair<int,int>>) << '\n';      //true

    //define to check for member type type size_type:
    auto hasSizeType = isValid([](auto x) -> 
    typename decltype(valueT(x))::size_type
    {
    });

    struct CX
    {
        using size_type = std::size_t;
    };

    cout << "hasSizeType: " << hasSizeType(type<CX>) << '\n';           //true

    if(!hasSizeType(type<int>))
    {
        cout << "int has no size_type \n";
    }

    //define to check for <:
    auto hasLess = isValid([](auto x, auto y) -> 
    decltype(valueT(x) < valueT(y))
    {
    });
    
    //最终的输出结果与想象的答案不一样。。。。不知道是不是底层环境所致。
    cout << "hasLess(42,type<char>): " << hasLess(type<int>,type<char>) << "\n";         //yields true
    cout << "hasLess(type<string>,type<string>): " << hasLess(type<string>,type<string>) << "\n";         //yields true
    cout << "hasLess(type<string>,type<int>): " << hasLess(type<string>,type<int>) << "\n";         //yields false
    cout << "hasLess(type<string>,\"hello\"): " << hasLess(type<string>,type<char*>) << "\n";         //yields true
    return 1;
}