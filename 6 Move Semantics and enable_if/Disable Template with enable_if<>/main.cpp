#include <iostream>
#include <typeinfo>
//Since C++11 the c++standard library provides a helper template std::enable_if<> to ignore
//function templates under certain compile-time conditions.

template<typename T>
//额。。。都没有见过这种用法。。。。。
//this definition of foo<> is ignored if sizeof(T) > 4 yields flase.
//if sizeof(T) > 4 yields true, the function template instance expands to void foo(){}
//即，不满足条件时，忽略该定义；满足条件时，使用::type 返回类型。
typename std::enable_if<(sizeof(T) > 4)>::type foo()
{

}

//since C++14
//use enable_if_t to skip typename and ::type.
// template<typename T>
// std::enable_if_t<(sizeof(T) > 4)> foo()
// {

// }

//second argument is passed
//the enable_if construct expands to this second argument if the expression yields true.
template<typename T>
std::enable_if_t<(sizeof(T)>4),T> foo()
{
    return T();
}

//optimized
template<typename T, typename = std::enable_if_t<(sizeof(T) > 4)>>
void foo1()
{
    std::cout<<"foo1()\n";
}

//equal above if sizeof(T) > 4
// template<typename T, typename = void>
// void foo()
// {

// }

//or you can define your own name.
// template<typename T>
// using EnableIfSizeGreater4 = std::enable_if_t<(sizeof(T)>4)>;

// template<typename T, typename = EnableIfSizeGreater4<T>>
// void foo()
// {

// }

//test: return value type.
template<typename T, typename = std::enable_if_t<(sizeof(T) > 4)>>
T foo1(T value)
{
    std::cout<<"T foo1()\n";
    return T();
}

//test: typeid
//optimized
template<typename T, typename = std::enable_if_t<std::is_same_v<T,int>>>
// template<typename T, typename = std::enable_if_t<(sizeof(T) == 4)>>
void foo2()
{
    std::cout<<"foo2()\n";
}

int main()
{
    // foo1<int>();//undefine error;
    foo1<double>();
    // auto result = foo1<int>(3);//undefine error
    auto result = foo1<double>(3.3);

    // foo1<double,int>();//额。。。若是有2个参数输入的话，无论如何都会成功的。

    foo2<double>();//这个不成功是在预期范围内。。。
    foo2<int>();
    return 1;
}