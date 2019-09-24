#include <iostream>
#include <utility>
#include <type_traits>  //for true_type, false_type, and void_t

template<typename T1, typename T2>
struct PlusResultT
{
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
};

template<typename T1, typename T2>
using PlusResult = typename PlusResultT<T1,T2>::Type;

template<typename T>
class Array
{
public:

template<typename T1, typename T2>
Array<typename PlusResultT<T1,T2>::Type> operator+ (Array<T1>const& a, 
                                                    Array<T2> const& b);

};

/*
Clearly, using PlusResultT<> here will lead to an error if no corresponding operator+
is defined for the array element.
*/
// //declare + for arrays of different element types:
// template<typename T1, typename T2>
// Array<typename PlusResultT<T1,T2>::Type> operator+ (Array<T1>const& a, 
//                                                     Array<T2> const& b);

class A
{
private:
    /* data */
public:
    A(/* args */) = default;
    ~A() = default;
};

class B
{
public:
    B() = default;
    ~B() = default;
};

void addAB(Array<A> arrayA,Array<B> arrayB)
{
    //Error: fails in instantiation of PlusResultT<A,B>
    auto sum = arrayA + arrayB;
}

/*
This has a remarkable consequence: It means that the program may fail
to compile even if we add a spcific overload to adding A and B arrays, 
because c++ does not specify whether the types in a function template are actually
instantiated if another overload would be better.
*/
//declare generic + for arrays of different element types:
template<typename T1, typename T2>
Array<typename PlusResultT<T1, T2>::Type> operator+ (Array<T1> const&,
                                                    Array<T2> const&);

//overload + for concrete types:
Array<A> operator+ (Array<A> const& arrayA, Array<B> const& arrayB);

void addAB(Array<A> const& arrayA, Array<B> const& arrayB)
{
    //Error?: depends on whether the compiler
    /*
    If the compiler can determine that the second declaration of operator+
    is a better match without performing deduction and substitution on the first(template)
    declaration of operator+, it will accept this code.
    */
    auto sum = arrayA + arrayB;
    //...                               //instantiates PlusResultT<A,B>
}


//implement
//primary template:
template<typename, typename, typename = std::void_t<>>
struct HasPlusT : std::false_type
{
};

//partial specialization (may be SFINAE'd away):
template<typename T1, typename T2>
struct HasPlusT<T1, T2, std::void_t<decltype(std::declval<T1>() + std::declval<T2>())>> : std::true_type
{
};


//pluse3.cpp
template<typename T1, typename T2, bool = HasPlusT<T1, T2>::value>
struct PlusResultT          //parimary template, used when HasPlusT yields true
{
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
};

template <typename T1, typename T2>
struct PlusResultT<T1, T2, false>           //partial specialization, used otherwise
{
    
};


//another sample
template<typename C, bool = HasMemberT_value_type<C>::value>        //typename的定义template的使用方式
struct ElementT
{
    using Type = typename C::value_type;            //typename的嵌套从属类型的使用方式
};

template<typename C>
struct ElementT<C,false>
{
};







int main()
{

    return 1;
}