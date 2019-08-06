#include <iostream>


// template<typename T>
// typename T::size_type len(T const& t)
// {
//     return t.size();
// }

/*
There is a common pattern or idiom to deal with such a situation:
• Specify the return type with the trailing return type syntax (use auto at the front and -> before the return type at the end).

• Define the return type using decltype and the comma operator.

• Formulate all expressions that must be valid at the beginning of the comma operator (converted to void in case the comma operator is overloaded).

• Define an object of the real return type at the end of the comma operator.
*/

template <typename T>
auto len(T& t) -> decltype((void)(t.size()), T::size_type())
{
    return t.size();
}

int main()
{
    std::allocator<int> x;
    std::cout<< len(x) << '\n';             //ERROR: len() selected, but x has no size();
                                            //OK: then new len();
    return 1;
}