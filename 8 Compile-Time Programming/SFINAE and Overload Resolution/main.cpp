#include <iostream>

/*
We say “we SFINAE out a function” if we mean to apply the SFINAE mechanism to ensure that 
function templates are ignored for certain constraints by instrumenting the template code to 
result in invalid code for these constraints.
 */
int main()
{
    return 1;
}