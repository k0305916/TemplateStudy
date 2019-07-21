#include <iostream>

template<typename T>
void printR(T const& arg)
{

}


int main()
{
    std::string const c = "hi"; 
    printR(c); //                           T deduced as std::string, arg is std::string const&

    printR("hi");                           // T deduced as char[3], arg is char const(&)[3]
    int arr[4]; 
    printR(arr);                            // T deduced as int[4], arg is int const(&)[4]
}