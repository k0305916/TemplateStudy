#include <iostream>
#include <deque>

template<typename T>
class Stack
{
    private:
        std::deque<T> elems;

    public:
        void push(T const& elem)            //push element
        {
            elems.push_back(elem);
        }
        void pop()                          //pop element
        {
            elems.pop();
        }
        T const& top() const               //return pop element;
        {
            return elems.top();
        }
        bool empty() const              //return whether the stack is empty
        {
            return elems.empty();
        }

        //assign stack of elements of type T2
        template<typename T2>
        Stack& operator=(Stack<T2> const&);

        //to get access to private members of Stack<T2> for any type T2:
        template<typename> friend class Stack;
};

#pragma region origin Version
// template<typename T>
//   template<typename T2>
// Stack<T>& Stack<T>::operator= (Stack<T2> const& op2)
// {
//     Stack<T2> tmp(op2);             //create a copy of the assigned stack
//     elems.clear();                  //remove existing elements
//     while(!tmp.empty())             //copy all elements
//     {
//         elems.push_front(tmp.top());
//         tmp.pop();
//     }
//     return *this;
// }
#pragma endregion

#pragma region friend class Version
template<typename T>
  template<typename T2>
Stack<T>& Stack<T>::operator= (Stack<T2> const& op2)
{
    elems.clear();                      //remove existing elements
    elems.insert(elems.begin(),op2.elems.begin(),op2.elems.end());  //insert at the beginning all elements from op2
    return *this;
}
#pragma endregion

int main()
{
    Stack<int> intStack;            //Stack for ints
    Stack<float> floatStack;        //stack for floats

    floatStack = intStack;          //OK: stacks have different types, but int converts to float.
}