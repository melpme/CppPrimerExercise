#include <iostream>

int main()
{
    int value = 10;
    while (value >= 0) {
        std::cout << value << " ";
        value--;
    }
    std::cout << std::endl;
    return 0;
}