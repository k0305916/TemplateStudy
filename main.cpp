#include <iostream>

template<typename T>
void passR(T&& arg)                 //arg declared as forwarding reference
{
    T x;                            // for passed lvalues x is a reference; which requires an initializer
}

int main()
{
    std::string s = "hi";
    passR(s);                           //OK: T deduced as std::string& (also the type of arg)
    passR(std::string("hi"));           //OK: T deduced as std::string, arg is std::string&&
    passR(std::move(s));                //OK: T deduced as std::string, arg is  std::string&&

    int arr[4];
    passR(arr);                         //OK: T deduced as int(&)[4] (also the type of arg)

    std::string const c = "hi";
    passR(c);                           //OK: T deduced as std::string const&
    passR("hi");                        //OK: T deduced as char const(&)[3]
    passR(arr);                         //OK: T deduced as int(&)[4] (also the type of arg)

    passR(42);                          //OK: T deduced as int
    int i;
    passR(i);                           //ERROR: T deduced as int&, which makes the declaration of x in passR() invalid.
    return 0;
}