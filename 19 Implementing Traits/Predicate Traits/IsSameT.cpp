#include <iostream>

//这是个小技巧：若相同类型，则match下一个，否则则是上一个。
//都不用写代码。。。。直接利用match机制就完成了。
template<typename T1, typename T2>
struct IsSameT
{
    static constexpr bool value = false;
};

template<typename T>
struct IsSameT<T,T>
{
    static constexpr bool value = true;
};

template<typename T1,typename T2>
constexpr bool isSame = IsSameT<T1,T2>::value;

//C++ provide: std::is_same<>


int main()
{
    return 1;
}