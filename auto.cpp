#include <iostream>

int main()
{
    []
    {
        std::cout << "Hello lamda\n";
    }();

    auto l = []
    {
        std::cout <<"Hello lamda 2\n";
    };

    l();
}