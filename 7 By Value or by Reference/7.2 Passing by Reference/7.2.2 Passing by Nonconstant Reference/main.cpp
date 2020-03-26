#include <iostream>

//version 1
template<typename T>
void outR(T& arg)
{

}

//version 2 -- optimized
template<typename T>
void outR(T& arg)
{
    if(std::is_array<T>::value)
    {
        std::cout<<"got array of " << std::extent<T>::value<<"elems\n";
    }
}

//If you want to disable passing constant objects to nonconstant references, you can do the following:
//1. Use a static assertion to trigger a compile-time error:
template<typename T>
void ourR(T& arg)
{
    static_assert(!std::is_const<T>::value,"out parameter of foo<T>(T&) is const");
}

//2. Disable the template for this case either by using std::enable_if<> (see Section 6.3 on page 98):
template<typename T, typename = std::enable_if_t<!std::is_const<T>::value>>
void outR(T& arg)
{

}

//3. concepts once they are supported (see Section 6.5 on page 103 and Appendix E):
template<typename T>
requires (!std::is_const_v<T>)
void outR(T& arg)
{

}


int main()
{
    //version 1 respond
    //Note that calling outR() for a temporary (prvalue) or an existing object passed with std::move() (xvalue) usually is not allowed.
    std::string returnString();
    std::string s = "hi";
    outR(s);                            //OK: T deduced as std::string, arg is std::string&
    // outR(std::string("hi"));          //Error: not allowed to pass a temporary(prvalue)
    // outR(returnString());           //Error: not allowed to pass a temporary(prvalue)
    // outR(std::move(s));             //Error: not allowed to pass an xvalue.

    //version 2 respond.
    std::string const returnConstString();
    std::string const c = "hi";
    outR(c);                        //OK: T deduced as std::string const
    outR("hi");                     //OK: T deduced as char const[3]
    outR(returnConstString());           //OK: same if returnString() returns const string
    outR(std::move(c));             //OK: T deduced as std::string const

    //version 1
    //You can pass raw arrays of nonconstant types, which again don’t decay:
    int arr[4];
    outR(arr);                      //OK: T deduced as int[4], arg is int(&)[4]
    return 0;
}