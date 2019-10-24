#include <iostream>

/*Additionally, it provides a type member BaseT that describes the type that the pointer points to.
 Note that this type member is only available when the original type was a pointer, 
 making this a SFINAE-friendly type trait (see Section 19.4.4 on page 424).
 */
template<typename T>
struct IsPointerT : std::false_type {           //primary template : by default not a pointer

};

template<typename T>
struct IsPointerT<T*> : std::true_type{         //partial specialization for pointers
    using BaseT = T;
};

//C++ standard library: std::is_pointer<>

int main()
{
    return 1;
}