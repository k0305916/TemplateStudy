#include <iostream>

//enum {value = sizeof(test<...>(0)) == 1};
//different platform have different value for sizeof function.

//Given that observation, we want to ensure that the return types of test() functions
//have different sizes on all platforms.

//solution:
// using Size1T = char;
// using Size2T = struct {char a[2];};

//or 
using Size1T = char(&)[1];
using Size2T = char(&)[2];

//then define test overloads as follow:
// template<...> static Size1T test(void*);  //checking test()
// template<...> static Size2T test(...);      //fallback

int main()
{
    std::cout << sizeof(Size1T)<<'\n';          //return 1;
    std::cout << sizeof(Size2T)<<'\n';          //return 2;
    return 1;
}