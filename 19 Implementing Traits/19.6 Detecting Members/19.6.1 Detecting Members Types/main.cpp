#include <iostream>
#include <type_traits>              //defines true_type and false_type


//helper to ignore any number of template parameters:
template<typename...>
using VoidT = void;

//primary template:
template<typename, typename = VoidT<>>
struct HasSizeTypeT : std::false_type
{
};

/*
As usual for predicate traits, we define the general case to be derived from std::false_type, 
because by default a type doesn’t have the member size_type.

This construct is valid if and only if type T has a member type size_type, 
which is exactly what we are trying to determine.
*/
//partial specialization (may be SFINAE'd away):
template<typename T>
struct HasSizeTypeT<T, VoidT<typename T::size_type>>: std::true_type
{
};

/*
Note that if the member type size_type is private, 
HasSizeTypeT yields false because our traits templates have no special access to their argument type, 
and therefore typename T::size_type is invalid (i.e., triggers SFINAE)
*/
struct CX
{
    using size_type = std::size_t;
};

struct CXR
{
    using size_type = char&;            //Note: type size_type is a reference type;
};

//Can use removeReference trait in the partial specialization of HasSizeTypeT.
// template<typename T>
// struct HasSizeTypeT<T, VoidT<RemoveReference<T>::size_type>> : std::true_type
// {
// };

// int main()
// {
//     std::cout << HasSizeTypeT<int>::value;              //false

//     std::cout << HasSizeTypeT<CX>::value;               //true

//     std::cout << HasSizeTypeT<CXR>::value;              //OK: prints true

//     std::cout << HasSizeTypeT<CX&>::value;              //OOPS: prints false

//     std::cout << HasSizeTypeT<CXR&>::value;             //OOPS: prints false
//     return 1;
// }