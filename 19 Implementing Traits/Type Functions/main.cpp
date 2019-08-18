#include <iostream>
#include <cstddef>  //?

template<typename T>
struct TypeSize{
    static std::size_t const value = sizeof(T);
};

int main()
{
    std::cout << "TypeSize<int>::value="<<TypeSize<int>::value<<'\n';
    return 1;
}