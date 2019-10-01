#include <iostream>
#include <type_traits>
#include <vector>
/*
Defining a trait such as HasSizeTypeT raises the question of how to parameterize the trait to be able to check for any member type name.

Unfortunately, this can currently be achieved only via macros, 
because there is no language mechanism to describe a “potential” name. 
The closest we can get for the moment without using macros is to use generic lambdas
*/
#define DEFINE_HAS_TYPE(MemType)                            \
    template<typename, typename = std::void_t<>>            \
    struct HasTypeT_##MemType : std::false_type{};          \
    template<typename T>                                    \
    struct HasTypeT_##MemType<T, std::void_t<typename T::MemType>> : std::true_type {};      //intentionally skipped
    

DEFINE_HAS_TYPE(value_type);
DEFINE_HAS_TYPE(char_type);

int main()
{
    std::cout << "int::value_type: " << HasTypeT_value_type<int>::value << '\n';

    std::cout << "std::vector<int>::value_type: " << HasTypeT_value_type<std::vector<int>>::value << '\n';

    std::cout << "std::iostream::value_type: " << HasTypeT_value_type<std::iostream>::value << '\n';

    std::cout << "std::iostream::char_type: " << HasTypeT_char_type<std::iostream>::value << '\n';

    return 1;
}