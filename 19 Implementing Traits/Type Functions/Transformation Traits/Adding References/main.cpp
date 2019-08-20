#include <iostream>

template<typename T>
struct AddLValueReferenceT{
    using Type = T&;
};

template<typename T>
using AddLValueReference = typename AddLValueReferenceT<T>::Type;

template<typename T>
struct AddRValueReferenceT
{
    using Type = T&&;
};

template<typename T>
using AddRValueReference = typename AddRValueRederenceT<T>::Type;

/*
which can be instantiated without instantiating a class template 
(and is therefore a lighter-weight process). However, this is risky, 
as we may well want to specialize these template for special cases. 
For example, as written above, we cannot use void as a template argument for these templates. 
A few explicit specializations can take care of that:
*/

template<>
struct AddLValueReferenceT<void>
{
    using Type = void;
};

template<>
struct AddLValueReferenceT<void const>
{
    using Type = void const;
};

template<>
struct AddLValueReferenceT<void volatile>
{
    using Type = void volatile;
};

template<>
struct AddLValueReferenceT<void const volatile>
{
    using Type = void const volatile;
};

//c++11/17 support std::add_lvalue_reference<>, std::add_rvalue_reference<>



int main()
{
    return 1;
}