#include <iostream>
#include <string>
#include <unordered_set>

class Customer
{
private:
    std::string name;

public:
    Customer(std::string const &n) : name(n) {}
    std::string getName() const { return name; }
};

//若要在自定义类型上使用无序容器，那么就要自己写以下2个函数：HASH计算+是否相等。
struct CustomerEq
{
    bool operator()(Customer const &c1, Customer const &c2) const
    {
        return c1.getName() == c2.getName();
    }
};

struct CustomerHash
{
    std::size_t operator()(Customer const &c) const
    {
        return std::hash<std::string>()(c.getName());
    }
};

//define class that combines operator() for variadic base classes;
template<typename... Bases>
struct Overloader : Bases...
{
    using Bases::operator()...; //OK since c++17
};


int main()
{
    //combine hasher and equality for customers in one type:
    using CustomerOP = Overloader<CustomerHash,CustomerEq>;
    std::unordered_set<Customer,CustomerHash,CustomerEq> coll1;//coll1 the same as coll2
    std::unordered_set<Customer,CustomerOP,CustomerOP> coll2;
    return 0;
}