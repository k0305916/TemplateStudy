#include <iostream>

/*
Traits returning a value require a trailing ::value (or similar member selection) to produce the result of the trait.
 In this case, constexpr variable templates (introduced in Section 5.6 on page 80) offer a way to reduce this verbosity.
*/
template<typename T1, typename T2>
constexpr bool IsSame = IsSameT<T1, T2>::value;

template<typename FROM, typename TO>
constexpr bool IsConvertible = IsConvertible<FROM, TO>::value;

int main()
{
    // //Just example:
    // if(IsSame<T,int> || IsConvertible<T,char>)
    //     ...
    // //instead of
    // if(IsSame<T,int>::value || IsConvertible<T, char>::value) ...
    return 1;
}