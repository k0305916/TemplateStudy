#include <iostream>
#include <deque>
#include <vector>
#include <cassert>
#include <memory>

//template<typename T,template<class Elem> class Cont = std::vector>               //before C++11
//额，由于C++17之前并未考虑到Alloc的问题。。。因此，需要明确申明出来。。。C++17之后，则不需要了。
template<typename T,template<typename Elem,typename Alloc=std::allocator<Elem>> class Cont = std::vector>           //额。。。Elem好像在下文都未用到。。。怎么回事？
//template<typename T,template<typename Elem> typename Cont = std::vector>      //Error before C++17
class Stack
{
private:
  Cont<T> elems;            //elements  
public:
    void push(T const&);            //push element
    void pop();                     //pop element
    T const& top() const;           //return top element
    bool empty() const             //return whether the stack is empty
    {
        return elems.empty();
    }

    //assign stack of elements of type T2
    template<typename T2, template<typename Elem2, typename = std::allocator<Elem2>> class Cont2>
    Stack<T,Cont>& operator= (Stack<T2,Cont2> const&);

    //to get access to private members of any Stack with elements of type T2
    template<typename, template<typename,typename>class>
    friend class Stack;
};

template<typename T, template<typename,typename> class Cont>
void Stack<T,Cont>::push(T const& elem)
{
    elems.push_back(elem);          //append copy of passed elem
}

template<typename T, template<typename,typename> class Cont>
void Stack<T,Cont>::pop()
{
    assert(!elems.empty());
    elems.pop_back();               //remove last element
}

template<typename T, template<typename,typename> class Cont>
T const& Stack<T,Cont>::top() const
{
    assert(!elems.empty());
    return elems.back();                    //return copy of last element
}

template<typename T, template<typename,typename> class Cont>
    template<typename T2, template<typename,typename> class Cont2>
Stack<T,Cont>& Stack<T,Cont>::operator=(Stack<T2,Cont2> const& op2)
{
    elems.clear();      //remove existing elements
    elems.insert(elems.begin(),op2.elems.begin(),op2.elems.end());   // insert at the beginning all elements from op2
    return *this;
} 


int main()
{
    Stack<int> iStack;
    Stack<float> fStack;

    //mainpulate int stack
    iStack.push(1);
    iStack.push(2);
    std::cout<< "iStack.top():"<<iStack.top()<<std::endl;

    //mainpulate float stack;
    fStack.push(3.3);
    std::cout<<"fStack.top():"<<fStack.top()<<std::endl;

    //assign stack of different type and mainpulate again
    fStack = iStack;
    fStack.push(4.4);
    std::cout<<"fStack.top():"<<fStack.top()<<std::endl;

    //stack for doubless using a vector as internal container
    Stack<double,std::vector> vStack;
    vStack.push(5.5);
    vStack.push(6.6);
    std::cout<<"vStack.top():"<<vStack.top()<<std::endl;

    vStack = fStack;
    std::cout<<"vStack:";
    while(!vStack.empty())
    {
        std::cout<< vStack.top()<<" ";
        vStack.pop();
    }

    // //替换成foreach
    // for(auto begin = std::begin(vStack);begin!=std::end(vStack);++begin)
    // {

    // }
    std::cout<< std::endl;
    return 1;
}