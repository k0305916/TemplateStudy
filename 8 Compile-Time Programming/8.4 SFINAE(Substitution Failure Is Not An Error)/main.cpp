#include <iostream>
#include <vector>

/*
Here, we define two function templates len() taking one generic argument:

1. The first function template declares the parameter as T(&)[N], 
    which means that the parameter has to be an array of N elements of type T.

2. The second function template declares the parameter simply as T, 
    which places no constraints on the parameter but returns type T::size_type, 
    which requires that the passed argument type has a corresponding member size_type.
 */

//version 1
//number of elements in a raw array:
template<typename T, unsigned N>
std::size_t len(T(&)[N])
{
    return N;
}

//number of elements for a type having size_type:
template<typename T>
typename T::size_type len(T const& t)
{
    return t.size();
}

//version2
// //number of elements in a raw array:
// template<typename T,unsigned N>
// std::size_t len(T(&)[N])
// {
//     return N;
// }

// //number of elements for a type having size_type:
// template<typename T>
// typename T::size_type len(T const& t)
// {
//     return t.size();
// }

//fallback for all other types:
std::size_t len(...)
{
    return 0;
}

int main()
{
    int a[10];
    std::cout << len(a);            //OK: only len() for array matches(best match)
    std::cout << len("temp");       //OK: only len() for array matches(best match)

    std::vector<int> v;
    std::cout << len(v);            //OK: only len() for a type with size_type matches(best match)

    int* p;
    std::cout << len(p);            //compile-time ERROR: no matching len() function found
                                    //OK: only fallback len() matches

    std::allocator<int> x;
    std::cout << len(x);            //run-time ERROR: len() function found, but cannot size()
                                    // ERROR: 2nd len() function matches best, but cannot call size() for x
    return 1;
}