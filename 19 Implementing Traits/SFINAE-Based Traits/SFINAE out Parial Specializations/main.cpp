#include <iostream>
#include <type_traits>          //defines true_type and false_type
#include <utility>              // for c++17 example
#include "19 Implementing Traits/Predicate Traits/IsSameT.cpp"

struct NoDefaultConstruct
{
    NoDefaultConstruct() = delete;
};


/*
explain:
  we define the general case to be derived form std::false_type,because
  by default a type doesnot have the member size_type.

  The interesting feature here is the second template argument that defaults to 
  the type of a helper VoidT. It enables us to provide parial specializations that
  use an arbitrary number of compile-time type constructs.

  In this case, we need only one construct: decltype(T()) to check again 
  whether the default constructor for T is valid.
*/

//helper to ignore any number of template parameters:
template<typename...>
using VoidT = void;

//primary template
template<typename, typename = VoidT<>>
struct IsDefaultConstructibleT : std::false_type
{
};

//partial specialization(may be SFINAE'd away):
template<typename T>
struct IsDefaultConstructibleT<T,VoidT<decltype(T())>> : std::true_type
{
};

//In C++17, the c++ standard library introduced a type trait std::void_t<> that 
//corresponds to the type VoidT introduced here.