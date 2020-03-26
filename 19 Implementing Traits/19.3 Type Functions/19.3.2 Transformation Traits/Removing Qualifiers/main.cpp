#include <iostream>

template<typename T>
struct RemoveConstT
{
    using Type = T;
};

template<typename T>
struct RemoveConstT<T const>
{
    using Type = T;
};

template<typename T>
using RemoveConst = typename RemoveConstT<T>::Type;

/*
Moreover, transformation traits can be composed, such as creating a RemoveCVT trait that removes both const and volatile.
*/
template<typename T>
struct RemoveCVT : RemoveConstT<typename RemoveVolatileT<T>::Type>
{
};

template<typename T>
using RemoveCV = typename RemoveCVT<T>::Type;

//C++11/17 support std::remove_volatile<>, std::remove_const<>, std::remove_cv<>



int main()
{
    return 1;
}