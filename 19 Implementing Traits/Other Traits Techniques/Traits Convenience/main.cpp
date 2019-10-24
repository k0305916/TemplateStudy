#include <iostream>

template<typename T1, typename T2>
Array<typename RemoveCVT<typename RemoveReferenceT<typename PlusResultT<T1, T2>::Type>::Type>::Type>
operator+ (Array<T1> const&, Array<T2> const&);

int main()
{
    return 1;
}