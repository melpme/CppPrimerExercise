#include <iostream>

int main()
{
    long double ld = 3.1415926;
    int a{ld}, b = {ld};
    int c(ld), d = ld;
    return 0;
}