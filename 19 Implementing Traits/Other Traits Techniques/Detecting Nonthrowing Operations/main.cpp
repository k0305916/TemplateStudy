#include <iostream>
#include <utility>              // for declval
#include <type_traits>          // for bool_coinstant true_type false_type

#pragma region isnothrowmoveconstructible1
// template<typename T>
// struct IsNothrowMoveConstructibleT : std::bool_constant<noexcept(T(std::declval<T>()))>     // std::bool_constant?
// {
// };
#pragma endregion

#pragma region isnothrowmoveconstructible2
//primary template:
template<typename T, typename = std::void_t<>>
struct IsNothrowMoveConstructibleT : std::false_type
{};

//partial specialization (may be SFINAE'd away):
template<typename T>
struct IsNothrowMoveConstructibleT<T, std::void_t<decltype(T(std::declval<T>()))>> : std::bool_constant<noexcept(T(std::declval<>T()))>
{
};
#pragma endregion

template<typename T1, typename T2>
class Pair{
    T1 first;
    T2 second;
public:
    // Pair(Pair&& other) : first(std::forward<T1>(other.first)), second(std::forward<T2>(other.second)){}         //这种的初始化，额，我还是第一次看到呢。。。开了眼界呀。
    Pair(Pair&& other) noexcept(IsNothrowMoveConstructibleT<T1>::value && IsNothrowMoveConstructibleT<T2>::value):
    first(std::forward<T1>(other.first)),second(std::forward<T2>(other.second)){}
};

//c++ standard: std::is_move_constructible<>