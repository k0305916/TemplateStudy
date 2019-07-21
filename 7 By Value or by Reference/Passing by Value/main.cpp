//适用于2种状况
//1. 直接用左值；
//2. decays，即将具体数组大小装成指针类型，增加实用性。
//When passing arguments by value, each argument must in principle be copied. 
//Thus, each parmeter becomes a copy of the passed argument.
//For classes, the object created as a copy generally is initialized by the copy constructor.

#include <iostream>

template<typename T>
void printV(T arg)
{

}

//Again, when passing the string, arg becomes a copy of s. 
//This time the copy is created by the copy constructor of the string class,
//which is a potentially expensive operation, 
//because in principle this copy operation creates a full or “deep” copy 
//so that the copy internally allocates its own memory to hold the value.
// void printV(std::string arg)
// {

// }

int main()
{
    std::string returnString();
    std::string s = "hi";
    printV(s);                  //copy constructor
    printV(std::string("hi"));  //copy usually optimezed away(if not, move constructor)
    printV(returnString());     //copy usually optimezed away(if not, move constructor)
    printV(std::move(s));       //move constructor

    std::string const c = "hi";
    printV(c);                  //c decays so that has type std::string

    printV("hi");               //decays to pointer so that arg has type char const*

    int arr[4];
    printV(arr);                //decays to pointer so that arg has type int*
}