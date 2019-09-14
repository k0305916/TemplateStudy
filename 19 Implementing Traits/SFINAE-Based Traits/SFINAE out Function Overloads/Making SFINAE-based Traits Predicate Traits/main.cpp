#include <iostream>
#include <type_traits>


//This way, we can also solve the problem that 
//on some platforms sizeof(char)==sizeof(long).

// template<...> static std::true_type test(void*);        //checking test()
// template<...> static std::false_type test(...);         //fallback

//????FROM????是什么？
//we no longer need the IsSameT trait:
// using Type = decltype(test<FROM>(nullptr));

//Formal IsDefaultConstructibleT
template<typename T>
struct IsDefaultConstructibleHelper
{
private:
    //test() trying substitute call of a default constructor for T passed as U:
    template<typename U, typename = decltype(U())>
    static std::true_type test(void*);

    //test() fallback
    template<typename>
    static std::false_type test(...);

public:
    using Type = decltype(test<T>(nullptr));
};

template<typename T>
struct IsDefaultConstructibleT : IsDefaultConstructibleHelper<T>::Type
{
};



int main()
{
    return 1;
}