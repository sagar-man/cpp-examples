#include <iostream>

int main()
{
    int x = 0;
    int y = 42;

    auto qq = [x, &y]
    {
        std::cout <<"inside lamda:: value of x: " << x <<"\n";
        std::cout <<"inside lamda:: value of y: " << y <<"\n";
        ++y;
    };

    x = y = 77;
    
    qq();
    qq();

    std::cout << "outside lamda:: value of x: " << x <<"\n";
    std::cout <<"outside lamda:: value of y: " << y <<"\n";

    std::cout <<"final value of y: " << y <<"\n";

    return 0;
}