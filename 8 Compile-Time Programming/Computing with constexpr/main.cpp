#include <iostream>

//C++11 version
constexpr bool DoIsPrime(unsigned p, unsigned d)        //P:number to check, d: current divisor
{
    return d!=2?(p%d!=0) && DoIsPrime(p,d-1)        //check this and smaller divisors
                : (p%2!=0);                         // end recursion if divisor is 2
}

constexpr bool isPrime(unsigned p)
{
    return p<4?(p<2)                    //handle special cases
                :DoIsPrime(p,p/2);      //start recursion with divisor from p/2
}

//c++14 version
constexpr bool isPrime(unsigned int p)
{
    for(unsigned int d=2; d<=p/2;++d)
    {
        if(p%d ==0)
            return false;               //found divisor without remainder
    }
    return p>1;                         // no divisor without remainder found
}


bool fiftySevenIsPrime()
{
    return isPrime(57);                 //evaluated at compile or running time
}

int main()
{
    constexpr bool b1 = isPrime(9);     // evaluated at compile time

    int x;
    std::cout<<isPrime(x);              //evaluated at run time
    return 0;
}