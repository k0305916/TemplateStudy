#include <iostream>
#include <deque>
#include <vector>

class BoolString
{
private:
    std::string value;

public:
    BoolString(std::string const &s) : value(s) {}

    template <typename T = std::string>
    T get() const //get value(converted to T)---??若是转成不能兼容的类型呢？
    {
        return value;
    }
};

//full specialization for BoolString::getValue<>() for bool
template <>
inline bool BoolString::get<bool>() const
{
    return value == "true" || value == "1" || value == "on";
}

int main()
{
    std::cout << std::boolalpha; //what is it?
    BoolString s1("hello");
    std::cout << s1.get() << std::endl;       //prints hello
    std::cout << s1.get<bool>() << std::endl; //prints false

    BoolString s2("on");
    std::cout<<s2.get<bool>()<<std::endl;   //prints true
}