#include <iostream>
#include <type_traits>
#include <string>
#include <typeinfo>

template <typename T1>
struct IsCharT : std::false_type
{
    // static constexpr bool value = std::is_same<T1, char>::value;
    // static constexpr bool value = std::is_same<decltype(std::declval<T1>()), char>::value;
    static constexpr bool value = std::is_same<decltype(T1()), char>::value;

    template<typename F, typename T, std::enable_if_t<std::is_same<F,char>::value,char> = 0>
    static std::true_type test(void*);

    template<typename, typename>
    static std::false_type test(...);
};

template<typename FROM>
template<typename F, typename T, std::enable_if_t<std::is_same<F,char>::value,char>>
std::true_type IsCharT<FROM>::test(void*)
{
    std::cout << "std::true_type IsCharT<FROM>::test(void*)\n";
}

template<typename FROM>
template<typename, typename>
std::false_type IsCharT<FROM>::test(...)
{
    std::cout << "std::false_type IsCharT<FROM>::test(...)\n";
}

int main()
{
    // auto result = IsCharT<double>::value;
    // std::cout << "IsCharT<double>::value: " << result << '\n';

    // result = IsCharT<char>::value;
    // std::cout << "IsCharT<char>::value: " << result << '\n';

    // result = IsCharT<std::string>::value;
    // std::cout << "IsCharT<char>::value: " << result << '\n';

    auto b = 1;
    void* pb = &b;
    IsCharT<double> a;
    auto result = a.test<char,int>(pb);
    std::cout << "a.test<char,int>(): " << result.value << '\n';

    auto result11 = a.test<int,int>(pb);
    std::cout << "a.test<int,int>(): " << result11.value << '\n';

    auto result1 = a.test<int,int>();
    std::cout << "a.test<int,int>(): " << result1.value << '\n';

    return 1;
}