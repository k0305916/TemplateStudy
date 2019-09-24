#include <iostream>
#include <type_traits>          //for true_type and false_type
#include <utility>              //for declval

template<typename FROM, typename TO>
struct IsConvertibleHelper
{
    private:
        //test() trying to call the helper aux(TO) for a FROM passed as F:
        static void aux(TO);

        /*
        Here, FROM and To are completely determinded when this member function template
        is parsed, and therefore a pair of types for which the conversion is not valid(e.g., double* and int*)
        will trigger an error right away, before any call to test()(and therefore outside any SFINAE context).
        For that reason, we introduce F as a specific member function template parameter:
        */
        template<typename F, typename T, typename = decltype(aux(std::declval<F>()))>
        static std::true_type test(void*);

        // template<typename = decltype(aux(std::declval<FROM>()))>
        // static char test(void*);                                                        //does not work

        template<typename F, typename = decltype(aux(std::declval<F>()))>
        static char test(void*);

        //test() fallback:
        template<typename, typename>
        static std::false_type test(...);
    public:
        using Type = decltype(test<FROM>(nullptr));
        static constexpr bool value = std::is_same<decltype(test<FROM>(nullptr)), char>;    //这句话没有看懂。。。啥意思呀。。。
                                                                                                //难道只是为了判断是否为char？   额，不懂耶。
};

template<typename FROM, typename TO>
template<typename F, typename T, typename>
std::true_type IsConvertibleHelper<FROM,TO>::test(void*)
{

}

template<typename FROM, typename TO>
template<typename, typename>
std::false_type IsConvertibleHelper<FROM,TO>::test(...)
{

}

template<typename FROM, typename TO>
struct IsConvertibleT : IsConvertibleHelper<FROM, TO>
{
};

template<typename FROM, typename TO>
using IsConvertible = typename IsConvertibleT<FROM, TO>::type;

template<typename FROM, typename TO>
constexpr bool isConvertible = IsConvertibleT<FROM, TO>::value;         //value是默认拥有的？


int main()
{
    auto result = IsConvertibleT<int, int>::value;               //yields true
    std::cout << "IsConvertibleT<int, int>::value: " << result <<'\n';
    result = IsConvertibleT<int, std::string>::value;           //yields false
    std::cout << "IsConvertibleT<int, std::string>::value: " << result <<'\n';
    result = IsConvertibleT<char const*, std::string>::value;   //yields true
    std::cout << "IsConvertibleT<char const*, std::string>::value: " << result <<'\n';
    result = IsConvertibleT<std::string, char const*>::value;   //yields false
    std::cout << "IsConvertibleT<std::string, char const*>::value: " << result <<'\n';
    return 1;
}