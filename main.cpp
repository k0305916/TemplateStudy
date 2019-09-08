#include <iostream>
#include <string>

template<typename T1, typename T2>
struct PlusResutlT
{
    //直接通过sample相加来得到返回类型。。。。。
    //这个技巧很棒。。。但是真的能成功嘛？
    //答案：真的可以成功也。。。。只要符合2个类型确实都可以进行隐性转换。。。例如，int->double,char->int
    using Type = decltype(T1() + T2());
};

int main()
{
    PlusResutlT<int,double> a;
    PlusResutlT<int,std::string>::Type b;
    return 1;
}