#include <iostream>
#include <utility>
#include <string>
#include <type_traits>

// //since c++17
// template<typename STR,typename=std::enable_if_t<std::is_convertible_v<STR,std::string>>>
// Person(STR&& n);

// //another way
// template<typename T>
// using EnableIfString = std::enable_if_t<std::is_convertible_v<T,std::string>>;

// template<typename STR, typename=EnableIfString<STR>>
// Person(STR&& n);

//whole Persion expression
template <typename T>
using EnableIfString = std::enable_if_t<std::is_convertible_v<T, std::string>>;

// //it is OK too.
// template <typename T>
// using EnableIfString = std::enable_if_t<std::is_convertible_v<std::string, T>>;

// //c++14 version
// template<typename T>
// using EnableIfString = std::enable_if_t<std::is_convertible<T,std::string>::value>;

// //C++11 version
// template<typename T>
// using EnableIfString = typename std::enable_if<std::is_convertible<T,std::string>::value>::type;

#pragma region Disabling Special Member Functions
template<typename T>            //just for optimized
class C
{
private:
    /* data */
public:
    //user-define the predefined copy constructor as deleted
    //(with conversion to volatile to enable better matches)
    C(C const volatile&) = delete;

    // //note that normally we can not use enable_if<> to diable the predefined copy/move constructor and/or
    // //assignment operators.
    // template<typename T>
    // C(T const&)
    // {
    //     std::cout<<"tmpl copy constructor\n";
    // }

    //optimized
    // if T is no intergral type, provide copy constructor template with better match:
    template<typename U,typename=std::enable_if_t<!std::is_integral<U>::value>>
    C(C<U> const&)
    {
        std::cout<<"tmpl copy constructor optimized.\n";
    }
    C(){}
    ~C(){}
};

#pragma endregion

class Person
{
private:
    std::string name;

public:
    //generic constructor for passed initial name;
    template <typename STR, typename = EnableIfString<STR>>
    explicit Person(STR &&n) : name(std::forward<STR>(n))
    {
        std::cout << "TMPL-CONSTR for '" << name << "'\n";
    }

    //copy and move constructor:
    Person(Person const &p) : name(p.name)
    {
        std::cout << "COPY-CONST Person '" << name << "'\n";
    }

    Person(Person &&p) : name(std::move(p.name))
    {
        std::cout << "MOVE-CONSTR Person '" << name << "'\n";
    }
};
int main()
{
    std::string s = "sname";
    Person p1(s);             //init with string object => calls TMPL-CONSTR
    Person p2("tmp");         //init with string literal => calls TMPL-CONSTR
    Person p3(p1);            //OK => calls COPY-CONSTR
    Person p4(std::move(p1)); //OK => calls MOVE-CONST

    C x;
    // C y{x};                    //still uses the predefined copy constructor(not the member template);
    C y{x};                    //if delete predefined copy construct, then use member template;

    C z{3};
    return 1;
}
