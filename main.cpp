#include <iostream>
#include <type_traits>

template <typename T1>
struct IsCharT : std::false_type
{
    static constexpr bool value = std::is_same<T1, char>::value;
};

int main()
{
    auto result = IsCharT<double>::value;
    std::cout << "IsCharT<double>::value: " << result << '\n';

    result = IsCharT<char>::value;
    std::cout << "IsCharT<char>::value: " << result << '\n';
    return 1;
}