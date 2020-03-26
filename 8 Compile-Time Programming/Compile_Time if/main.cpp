#include <iostream>

template<typename T, typename... Types>
void print(T const& firstArg, Types const&... args)
{
    std::cout<<firstArg<<'\n';
    if constexpr(sizeof...(args) > 0)
    {
        print(args...);                     //code only available if sizeof...(args)>0   (since c++17)
    }
}

template<typename T>
void foo(T t)
{
    //Note that if constexpr can be used in any function, not only in templates.
    if constexpr(std::is_integral_v<T>)
    {
        if( t> 0)
            foo(t-1);               //OK
    }
    else
    {
        undeclared(t);          //error if not declared and not discarded(i.e. T is not integral)
        undeclared();           //error if not declared (even if discarded)
        static_assert(false, "no integral");        //always asserts(even if discarded)
        static_assert(!std::is_integral_v<T>,"no integral");        //OK
    }
}

/*
With this feature, we can, for example, use our isPrime() compile-time function, 
introduced in Section 8.2 on page 125, to perform additional code if a given size is not a prime number:
*/
template<typename T, std::size_t SZ>
void foo(std::array<T,SZ> const& coll)
{
    //Note that if constexpr can be used in any function, not only in templates.
    if constexpr(!isPrime(SZ))
    {
        //...                           //Special additional handling if the passed array has no prime number as size
    }
    //...
}

int main()
{
    if constexpr(std::numeric_limits<char>::is_signed)
    {
        foo(42);            //OK
    }
    else
    {
        undeclared(42);          //error if declared() not declared
        static_assert(false, "no integral");        //always asserts(even if discarded)
        static_assert(!std::numeric_limits<char>::is_signed,"char is unsigned");        //OK
    }
    return 1;
}
