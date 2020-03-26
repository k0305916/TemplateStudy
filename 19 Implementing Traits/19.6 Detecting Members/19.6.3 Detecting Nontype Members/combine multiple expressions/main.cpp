#include <iostream>
#include <utility>
#include <type_traits>
#include <string>

//primary template:
template<typename, typename, typename = std::void_t<>>
struct HasLessT : std::false_type
{
};

//partial specialization (may be SFINAE'd away):
template<typename T1, typename T2>
struct HasLessT<T1,T2,std::void_t<decltype(std::declval<T1>() < std::declval<T2>())>> : std::true_type
{
};

//we can use this trait to require that a template parameter T supports operator <:
template<typename T>
class C
{
    static_assert(HasLessT<T,T>::value,"Class C requires comparable elements.");
};

class A{};

int main()
{
    std::cout << "HasLessT<int, char>::value: " << HasLessT<int, char>::value << '\n';             //yields true
    std::cout << "HasLessT<std::string, std::string>::value: " << HasLessT<std::string, std::string>::value <<'\n';     //yiels true
    std::cout << "HasLessT<std::string, int>::value: " << HasLessT<std::string, int>::value << '\n';            //yields false
    std::cout << "hasLessT<std::string, char*>::value: " << HasLessT<std::string, char*>::value <<'\n';         //yields true

    C<int> a;
    C<A> b;
    return 1;
}