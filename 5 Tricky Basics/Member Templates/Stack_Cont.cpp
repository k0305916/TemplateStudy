#include <iostream>
#include <deque>
#include <vector>

//Cont默认使用std::deque
template <typename T, typename Cont = std::deque<T>>
class Stack
{
private:
    Cont elems;

public:
    void push(T const &elem) //push element
    {
        elems.push_back(elem);
    }
    void pop() //pop element
    {
        elems.pop();
    }
    T const &top() const //return pop element;
    {
        //这个地方，若是使用vector的话，是不存在top()的。。。那应该怎么处理呢？
        return elems.top();
    }
    bool empty() const //return whether the stack is empty
    {
        return elems.empty();
    }

    //assign stack of elements of type T2
    template <typename T2, typename Cont2>
    Stack &operator=(Stack<T2, Cont2> const &);

    //to get access to private members of Stack<T2> for any type T2:
    template <typename, typename>
    friend class Stack;
};

#pragma region friend class Version
template <typename T, typename Cont>
template <typename T2, typename Cont2>
Stack<T, Cont> &Stack<T, Cont>::operator=(Stack<T2, Cont2> const &op2)
{
    elems.clear();                                                   //remove existing elements
    elems.insert(elems.begin(), op2.elems.begin(), op2.elems.end()); //insert at the beginning all elements from op2
    return *this;
}
#pragma endregion

int main()
{
    //Stack for ints using a vector as an internal container
    //???为什么这个地方还需要使用std::vector<int>???定义上不是已经使用std::deque了嘛？？？
    Stack<int, std::vector<int>> vStack;

    vStack.push(42);
    vStack.push(7);

    std::cout << vStack.top() << std::endl;
}