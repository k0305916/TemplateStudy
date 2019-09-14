#include <iostream>
#include <utility>
#include <typeinfo>
//Fortunately, it is fairly easy to produce values for the + expression without requiring
//a constructor, by using a function that produces values of a given type T.
//For this, the c++ standard provides std::declval<>.

//The expression declval<T>() produces a value of type T without requeiring a default
//constructor(or any other operation).
// namespace std
// {
//     template<typename T>
//     add_rvalue_reference<T> declval() noexcept;
// }

template<typename T1, typename T2>
struct PlusResultT
{
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
};
template<typename T1, typename T2>
using PlusResult = typename PlusResultT<T1, T2>::Type;



int main()
{
    PlusResult<int,double> a;
    std::cout << typeid(a).name()<<'\n';
    return 1;
}