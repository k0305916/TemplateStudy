#include <iostream>
#include <type_traits>

using std::cout;
using std::endl;

int main() {
    typedef std::integral_constant<int, 1> one_t;

    cout << "one_t::value: " << one_t::value << endl;
    cout << "one_t::type::value: " << one_t::type::value << endl;


    typedef std::integral_constant<int, 0> one_0;
    int i = one_0::value;
    cout << "i::value: " << i << endl;

    return 1;
}