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

//the name of class == typename T::size_type
struct size_type
{
};

struct Sizeable : size_type
{
};


int main()
{
    auto result = HasSizeTypeT<Sizeable>::value;
    std::cout << "HasSizeTypeT<Sizeable>::value: " << result<<'\n';
    static_assert(HasSizeTypeT<Sizeable>::value,"Compiler bug: Injected class name missing.");
    return 1;
}