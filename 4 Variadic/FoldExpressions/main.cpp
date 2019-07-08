#include <iostream>

//Overloading Variadic and Nonvariadic Templates
template <typename T>
void print(T arg)
{
    std::cout << arg << std::endl;
}

template <typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << sizeof...(Types) << std::endl;
    if (sizeof...(args) > 0)
        std::cout << sizeof...(args) << std::endl;

    //solutionA: std::cout<<arg<<std::endl;//+print() function
    //solutionB: print(T arg)+print(T,...)
    print(firstArg);
    print(args...);
}

#pragma region FoldExpression Since C++ 17
template <typename... T>
auto foldSum(T... s)
{
    return (... + s); //Fold Expression
}
#pragma endregion

#pragma region NodeStuct
struct Node
{
    int value;
    Node *left;
    Node *right;
    Node(int i = 0) : value(i), left(nullptr), right(nullptr) {}
};

auto left = &Node::left;
auto right = &Node::right;

template <typename T, typename... TP>
Node *traverse(T np, TP... paths)
{
    foldprint(paths...);
    return (np->*...->*paths); //means: 顺着路径一直得到最后的path。
}
#pragma endregion

#pragma region Whitespace
template <typename T>
class AddSpace
{
private:
    T const &ref; //refer to argument passed in constructor
public:
    AddSpace(T const &r) : ref(r) {}
    //----amazing skill
    friend std::ostream &operator<<(std::ostream &os, AddSpace<T> s)
    {
        return os << s.ref << ' '; //output passed augument and a sapce
    }
};

template <typename... Args>
void AddSpaceprint(Args... args)
{
    (std::cout << ... << AddSpace(args)) << std::endl;
}
#pragma endregion

template <typename... Types>
void foldprint(Types const &... args)
{
    //std::cout << ... << args << std::endl;//Error....Why?
    (std::cout << ... << args) << std::endl; //额。。不懂这种打印出来的是啥。。。
}

int main()
{
#pragma region printExample
    // std::string s("world");
    // print(7.5, "hello", s);
#pragma endregion

#pragma region FoldExample
    Node *root = new Node{0};
    root->left = new Node{1};
    root->left->right = new Node{2};

    //traverse binary tree
    Node *node = traverse(root, left, right);
#pragma endregion

#pragma region AddSpaceExample
    AddSpaceprint(3, 5, 4);
#pragma endregion
    return 0;
}