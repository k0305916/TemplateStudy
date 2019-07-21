#include <iostream>


template<typename T>
void printR(T const& arg)
{

}

int main()
{
        std::string returnString();
        std::string s = "hi"; 
        
        printR(s);                  // no copy
        printR(std::string("hi"));  // no copy
        printR(returnString());     // no copy
        printR(std::move(s));       // no copy

        int i = 42;
        printR(i);                  // passes reference instead of just copying i
}