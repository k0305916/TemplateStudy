#include <iostream>
#include <array>

template<typename T,size_t ST>
std::array<T,ST> operator+ (std::array<T,ST> const&, std::array<T,ST> const&);

// template<typename T1, typename T2, size_t ST1, size_t ST2>
// std::array<???,???> operator+ (std::array<T1,ST1> const&, std::array<T2,ST2> const&);

// template<typename T1, typename T2>
// std::array<typename PlusResultT<T1, T2>::type> operator+ (std::array<T1> const&, std::array<T2> const&);

//or
// template<typename T1, typename T2>
// std::array<PlusResultT<T1, T2>> operator+ (std::array<T1> const&, std::array<T2> const&);

template<typename T1, typename T2>
struct PlusResutlT
{
    //直接通过sample相加来得到返回类型。。。。。
    //这个技巧很棒。。。但是真的能成功嘛？
    //答案：真的可以成功也。。。。只要符合2个类型确实都可以进行隐性转换。。。例如，int->double,char->int
    using Type = decltype(T1() + T2());
};

template<typename T1, typename T2>
using PlusResutl = typename PlusResultT<T1, T2>::Type;

// for remove reference and const
// template<typename T1, typename T2>
// std::array<RemoveCV<RemoveReference<PlusResutl<T1, T2>>>> operator+ (std::array<T1> const&, std::array<T2> const&);


int main()
{
    PlusResutlT<int,double> a;
    PlusResutlT<int,std::string>::Type b;
    return 1;
}