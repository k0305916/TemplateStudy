#include <iostream>
#include <string>
#include <utility>      // std::forward


//since C++17
template<typename STR>
requires std::is_convertible_v<STR,std::string>
Person(STR && n) : name(std::forward<STR>(n))
{

}

//or
template<typename T>
concept ConvertibleToSting = std::is_convertible_v<T,std::string>;

template<typenmae STR>
requires ConvertibleToSting<STR>
Person(STR&& n) : name(std::forward<STR>(n))
{

}


//or
template<typename STR>
Person(&& n):name(std::forward<STR>(n))
{

}


int main()
{

}