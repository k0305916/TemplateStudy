#include <iostream>

/*
In the following sections, we develop a suite of type traits that allow us to determine various properties of a given type. 
As a result, we will be able to write code specific for some types:
* if(ISClassT<T>::value) ...
* if constexpr (IsClass<T>) ...
* template<typenmae T, bool = IsClassT<T>>
class C{                //primary template for the general case
    ...
}

template<typename T>
class C<T,true>{            //partial specialization for class
    ...
}
*/


int main()
{
    return 1;
}