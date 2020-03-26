#include <iostream>
#include "ifthenelse.hpp"


//这种写法。。。真的是。。。完全就没有见过。。。也算是开了眼界了。。。
template<auto N>
struct SmallestIntT{
    using Type = typename IfThenElseT<N <= std::numeric_limits<char>::max(), char,
    typename IfThenElseT<N <= std::numeric_limits<short>::max(), short,
    typename IfThenElseT<N <= std::numeric_limits<int>::max(), int,
    typename IfThenElseT<N <= std::numeric_limits<long>::max(), long,
    typename IfThenElseT<N <= std::numeric_limits<long long>::max(), long long, //then
                                                                        void    //fallback
                                                                        >::Type
                                                                    >::Type
                                                                >::Type
                                                            >::Type
                                                        >::Type;
};

//ERROR: undefined behavior if T is bool or no integral type:
/*
The instantiation of UnsignedT<bool> is still undefined behavior, because the compiler will still attempt to form the type from:
typename std::make_unsigned<T>::type
*/
// template<typename T>
// struct UnsignedT
// {
//     using Type = IfThenElse<std::is_integral<T>::value && ! std::is_same<T,bool>::value,
//     typename std::make_unsigned<T>::type, T>;
// };

//To address this problem, we need to add an additional level of indirection, 
//so that the IfThenElse arguments are themselves uses of type functions that wrap the result:
//yield T when using member Type:
template<typename T>
struct IdentityT
{
    using Type = T;
};

//to make unsigned after IfThenElse was evaluated:
template<typename T>
struct MakeUnsignedT
{
    using Type = typename std::make_unsigned<T>::type;
};

template<typename T>
struct UnsignedT
{
    using Type = typename IfThenElse<std::is_integral<T>::value && !std::is_same<T,bool>::value,
                            MakeUnsignedT<T>,
                            IdentityT<T>
                            >::Type;
};

//C++ standard: std::conditional<>
//With it, the UnsignedT trait would be defined as follows:
// template<typename T>
// struct UnsignedT
// {
//     using Type = typename std::onditional_t<std::is_integral<T>::value && !std::is_same<T,bool>::value,
//                             MakeUnsignedT<T>,
//                             IdentityT<T>
//                             >::Type;
// };