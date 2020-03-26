#include <iostream>
#include <utility>
#include <typeinfo>

//https://www.hashcoding.net/2015/12/21/SFINAE%E3%80%81std-declval%E6%9D%82%E8%B0%88/

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
    //直接通过sample相加来得到返回类型。。。。。
    //这个技巧很棒。。。但是真的能成功嘛？
    //答案：真的可以成功也。。。。只要符合2个类型确实都可以进行隐性转换。。。例如，int->double,char->int
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
};
template<typename T1, typename T2>
using PlusResult = typename PlusResultT<T1, T2>::Type;



int main()
{
    PlusResult<int,double> a;           //OK
    //PlusResult<int,std::string> a;           //Failed.
    std::cout << typeid(a).name()<<'\n';
    return 1;
}