#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>

template<typename T>
struct ElementT;                //primary template

template<typename T>
struct ElementT<std::vector<T>>     //pritial specialization for std::vector
{
    using Type = T;
};

template<typename T>
struct ElementT<std::list<T>>       //pritial specialization for std::list
{
    using Type = T;
};

template<typename T, std::size_t N>
struct ElementT<T[N]>               //pritial specialization for std::arrays of known bounds
{
    using Type = T;
};

template<typename T>
struct ElementT<T[]>                //pritial specialization for arrays of unknown bounds
{
    using Type = T;
};

//if the container types define a member type value_type (as the standard containers do), we can write the following:
template<typename C>
struct ElementT
{
    using Type = typename C::value_type;
};

//case 1
template<typename T>
void printElementType(T const& c)
{
    std::cout<<"Container of "<<typeid(typename ElementT<T>::Type).name()<<" elements.\n";
}

//case 2
template<typename T>
using ElementType = typename ElementT<T>::Type;

template<typename C>
ElementType<C> sumOfElements(C const& c)
{

}

int main()
{
    std::vector<bool> s;
    printElementType(s);

    int arr[42];
    printElementType(arr);
}