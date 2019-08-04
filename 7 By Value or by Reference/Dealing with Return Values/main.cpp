/*
There are a few cases where returning references is common programming practice:
• Returning elements of containers or strings (e.g., by operator[] or front())
• Granting write access to class members
• Returning objects for chained calls (operator<< and operator>> for streams and operator= for class objects in general)
 */
#include <string>
#include <iostream>
#include <memory>

template<typename T>
T retR(T&& p)           //p is a forwarding reference
{
    return T{};         //OOPS: returns by reference when called for lvalues
}

template<typename T>
T retV(T p)         //Note: T might become a reference
{
    return T{};     //OOPS: return a reference if T is a reference
}

//To be safe, you have two options:
//•Use the type trait std::remove_reference<> (see Section D.4 on page 729) to convert type T to a nonreference
template<typename T>
typename std::remove_reference<T>::type retV(T p)
{
    return T{};         //always returns by value
}

//• Let the compiler deduce the return type by just declaring the return type to be auto 
//(since C++14; see Section 1.3.2 on page 11), because auto always decays
template<typename T>
auto retV(T p)          //by-value return type deduced by compiler
{
    return T{};         //always returns by value.
}

int main()
{
    std::string* s = new std::string("whatever");
    auto& c = (*s)[0];
    delete s;
    std::cout<<c;          //run-time Error

    auto s = std::make_shared<std::string>("whatever");
    auto& c = (*s)[0];
    s.reset();
    std::cout<<c;           //run-time Error

    int x;
    retV<int&>(x);          //retT() instantiated for t as int&
}