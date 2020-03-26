#include <iostream>
#include <type_traits>          //for true_type and false_type
#include <utility>              //for declval
#include <typeinfo>

template<typename FROM, typename TO>
struct IsConvertibleHelper
{
    private:
        //test() trying to call the helper aux(TO) for a FROM passed as F:
        static void aux(TO){}

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

        // //这个与第一个test在某些条件下重复了。
        // template<typename F, typename = decltype(aux(std::declval<F>()))>
        // static char test(void*){}

        //test() fallback:
        template<typename, typename>
        static std::false_type test(...);
    public:
        // using Type = decltype(test<FROM>(nullptr));      //针对char test(void*)
        using Type = decltype(test<FROM,TO>(nullptr));      //针对第一个test
        // static constexpr bool value = std::is_same<decltype(test<FROM,TO>(nullptr)), char>::value;    //这句话没有看懂。。。啥意思呀。。。
                                                                                                //---哦，原来的版本少了个::value。。。补上之后就懂了。
                                                                                                //针对char test(void*)
                                                                                                //难道只是为了判断是否为char？   额，不懂耶。
                                                                                                //因为test的某个返回值就是char类型。。。
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
using IsConvertible = typename IsConvertibleT<FROM, TO>::Type;

template<typename FROM, typename TO>
constexpr bool isConvertible = IsConvertibleT<FROM, TO>::value;         //value是默认拥有的？

//C++ standard library: std::is_convertible<>

int main()
{
    IsConvertibleT<int, int> a;               //yields true
    // std::cout << "IsConvertibleT<int, int> a: " << a.value <<'\n';
    auto result = isConvertible<int, int>;               //yields true
    std::cout << "IsConvertibleT<int, int>::value: " << result <<'\n';
    // IsConvertible<int, int> result1;
    // std::cout << "IsConvertibleT<int, int>::value: " << typeid(result1).name <<'\n';            //char

    // result = isConvertible<int, std::string>;           //yields false  
                                                            //---并不是能编译之后，运行得到"false",而是连编译都通过不了
    // std::cout << "isConvertible<int, std::string>: " << result <<'\n';

    result = IsConvertibleT<char const*, std::string>::value;   //yields true
    std::cout << "IsConvertibleT<char const*, std::string>::value: " << result <<'\n';

    // result = IsConvertibleT<std::string, char const*>::value;   //yields false
    // std::cout << "IsConvertibleT<std::string, char const*>::value: " << result <<'\n';
    return 1;
}