#include <iostream>

template <typename T>
T add(T t1, T t2)
{
    return t1 + t2;
}

template <typename T, typename... args>
T add(T first, args... rest)
{
    return first + add(rest...);
}

int main()
{
    int x = 10;
    int y = 20;
    int ret = add(10,20,30,30);

    std::cout <<"result:" << ret <<"\n";
}