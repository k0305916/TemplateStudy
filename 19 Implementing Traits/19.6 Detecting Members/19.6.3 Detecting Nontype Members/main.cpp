#include <iostream>
#include <vector>
#include <utility>

/*
Here, we use SFINAE to disable the partial specialization when &T::Member is not valid.
For that construct to be valid, the following must be true:
* Member must unambiguously identify a member of T(e.g., it connot be an overloaded member function name, 
or the name of multiple inherited members of the same name);
* The member must be accessible;
* The member must be a nontype, nonenumerator member(otherwise the prefix & would be invalid),
* If T::Member is a static data member, its type must not provide an operator& that makes &T::Member invalid(e.g., by making that operator inaccessible).
*/
#define DEFINE_HAS_MEMBER(Member)           \
    template<typename, typename = std::void_t<>>                \
    struct HasMemberT_##Member : std::false_type {};                               \
    template<typename T>                        \
    struct HasMemberT_##Member<T,std::void_t<decltype(&T::Member)>> : std::true_type{};     // intentionally skipped
    
DEFINE_HAS_MEMBER(size);
DEFINE_HAS_MEMBER(first);
DEFINE_HAS_MEMBER(third);
/*
Note that the HasMember trait only checks whether a single member with the corresponding name exists. 
The trait also will fail if two members exists, which might happen if we check for overloaded member functions.
*/
DEFINE_HAS_MEMBER(begin)

//the second way of HasMemberT_begin;
//primary template:
template<typename, typename = std::void_t<>>
struct HasBeginT : std::false_type{};

//partial specialization (may be SFINAE'd away):
template<typename T>
struct HasBeginT<T,std::void_t<decltype(std::declval<T>().begin())>> : std::true_type
{
};


int main()
{
    std::cout << "int::size: " <<HasMemberT_size<int>::value << '\n';

    std::cout << "std::vector<int>::size: " << HasMemberT_size<std::vector<int>>::value <<'\n';

    std::cout << "std::pair<int,int>::first: " << HasMemberT_first<std::pair<int,int>>::value<<'\n';

    std::cout << "std::pair<int,int>::third: " << HasMemberT_third<std::pair<int,int>>::value<<'\n';

    std::cout << "1. std::vector<int>::begin: " << HasMemberT_begin<std::vector<int>>::value << '\n';          //false, because of overload functions.

    std::cout << "2. std::vector<int>::begin: " << HasBeginT<std::vector<int>>::value << '\n';  // the better way.
    return 1;
}