#include <iostream>

int main()
{
    int id = 0;
    auto f = [id] () mutable
    {
        std::cout <<"inside lamda: value of id: "<<id <<"\n";
        ++id;
    };
    
    //id = 42;

    f();
    f();
    f();
    f();

    std::cout <<"outside lamda: value of id: " << id <<"\n";

    return 0;
}