#include <iostream>


//primary helper template:
template<int SZ, bool = isPrime(SZ)>
struct Helper;

//implementation if SZ is not a prime number:
template<int SZ>
struct Helper<SZ,false>
{
    /* data */
};

//implementation if SZ is a prime number:
template<int SZ>
struct Helper<SZ,true>
{
    /* data */
};

/*
Here, depending on whether the size of the std::array<> argument is a prime number, 
we use two different implementations of class Helper<>. 
This kind of application of partial specialization is broadly applicable to 
select among different implementations of a function template depending on properties of the arguments it’s being invoked for.
 */
template<typename T, std::size_t SZ>
long foo(std::array<T,SZ> const& coll)
{
    Helper<SZ> h;                   //implementation depends on whether array has prime number as size
}


int main()
{

}