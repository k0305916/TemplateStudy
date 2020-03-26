#include <functional> //for std::cref()
#include <string>
#include <iostream>

void printString(std::string const &s)
{
    std::cout << s << '\n';
}

template <typename T>
void printT(T arg)
{
    printString(arg); //might convert arg back to std::string
}

template <typename T>
void printV(T arg)
{
    std::cout << arg << '\n';
}

//the following fails because you can’t compare a reference wrapper with a char const* or std::string:
template <typename T1, typename T2>
bool isless(T1 arg1, T2 arg2)
{
    return arg1 < arg2;
}

//It also doesn’t help to give arg1 and arg2 a common type T:
template <typename T>
bool isless(T arg1, T arg2)
{
    return arg1 < arg2;
}

int main()
{
    std::string s = "hello";
    printT(s);            //print s passed by value
    printT(std::cref(s)); //print s passed "as if by reference"

    printV(s);            //OK
    printV(std::cref(s)); //ERROR: no operator <<< for reference wrapper defined

    if (isless(std::cref(s), "world")) //ERROR
        std::cout << "World" << '\n';

    if (isless(std::cref(s), std::string("world"))) //ERROR
        std::cout << "std::string(World)" << '\n';
}
