#include <iostream>

template <typename T, int N, int M>
bool less(T (&a)[N], T (&b)[M])
{
    for (int i = 0; i < N && i < M; ++i)
    {
        if (a[i] < b[i])
            return true;
        if (b[i] < a[i])
            return false;
    }
    return N < M;
}

template <int M, int N>
bool less(char const (&a)[N], char const (&b)[M])
{
    for (int i = 0; i < N && i < M; ++i)
    {
        if (a[i] < b[i])
            return true;
        if (b[i] < a[i])
            return false;
    }
    return N < M;
}

template <typename T>
struct MyClass; //primary template

template <typename T, std::size_t SZ>
struct MyClass<T[SZ]> //partial spcialization for arrays of known bounds
{
    static void print()
    {
        std::cout << "print() for T[" << SZ << "]\n";
    }
};

template <typename T, std::size_t SZ>
struct MyClass<T (&)[SZ]> //partial spec. for reference to arrays of known bounds
{
    static void print()
    {
        std::cout << "print() for T(&)[" << SZ << "]\n";
    }
};

template <typename T>
struct MyClass<T[]> //partial specialization for arrays of unknown bounds
{
    static void print()
    {
        std::cout << "print() for T[]\n";
    }
};

template <typename T>
struct MyClass<T (&)[]> //parital spec. for reference to arrays of unknown bounds
{
    static void print()
    {
        std::cout << "print() for T(&)[]\n";
    }
};

template <typename T>
struct MyClass<T *> //partial specialization for pointers
{
    static void print()
    {
        std::cout << "print() for T*\n";
    }
};

template<typename T1, typename T2, typename T3>
void foo(
    int a1[7],int a2[],             //pointers by language reles
    int (&a3)[42],                  //reference to array of known bound
    int (&x0) [],                   //reference to array of unknown bound
    T1 x1,                          //passing by value decays
    T2& x2,T3&& x3                  //passing by reference
)
{
    MyClass<decltype(a1)>::print();                 //uses MyClass<T*>
    MyClass<decltype(a2)>::print();                 //uses MyClass<T*>
    MyClass<decltype(a3)>::print();                 //uses MyClass<T(&)[SZ]>
    MyClass<decltype(x0)>::print();                 //uses MyClass<T(&)[]>
    MyClass<decltype(x1)>::print();                 //uses MyClass<T*>
    MyClass<decltype(x2)>::print();                 //uses MyClass<T(&)[]>
    MyClass<decltype(x3)>::print();                 //uses MyClass<T(&)[]>
}

int main()
{
    int x[] = {1, 2, 3};
    int y[] = {1, 2, 3, 4, 5};
    std::cout << less(x, y) << std::endl;

    std::cout << less("ab", "abc") << std::endl;

    int a[42];
    MyClass<decltype(a)>::print();                  //uses MyClass<T[SZ]>
    extern int x1[];                                //forward declare array----?
    MyClass<decltype(x)>::print();                  //uses MyClass<T[]>

    foo(a,a,a,x1,x1,x1,x1);
    return 0;
}
int x1[]={0,8,15};                                  //define forward-declared