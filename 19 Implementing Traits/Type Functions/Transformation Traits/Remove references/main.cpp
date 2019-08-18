//Remove References
#include <iostream>

template<typename T>
struct RemoveReferenceT
{
    using Type = T;
};

template<typename T>
struct RemoveReferenceT<T&>
{
    using Type = T;
};

template<typename T>
struct RemoveReferenceT<T&&>
{
    using Type = T;
};

//case 1
template<typename T>
using RemoveReference = typename RemoveReference<T>::Type;

//C++17 support: std::remove_reference<>


int main()
{

}