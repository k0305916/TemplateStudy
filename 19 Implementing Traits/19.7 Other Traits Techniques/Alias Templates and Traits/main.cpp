#include <iostream>

/*
alias templates offer a way to reduce verbosity. 
Rather than expressing a type trait as a class template with a type member Type, 
we can use an alias template directly. 
For example, the following three alias templates wrap the type traits used above:
*/
template<typename T>
using RemoveCV = typename RemoveCVT<T>::Type;

template<typename T>
using RemoveReference = typename RemoveReferenceT<T>::Type;

template<typename T>
using PlusResult = typename PlusResultT<T1, T2>::Type;

//Given these alias templates, we can simplify our operator+ declaration down to
template<typename T1, typename T2>
Array<RemoveCV<RemoveReference<PlusResult<T1,T2>>>>
operator + (Array<T1> const&, Array<T2> const&);

int main()
{
    return 1;
}