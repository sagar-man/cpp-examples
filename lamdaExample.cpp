#include <iostream>
#include <functional>

std::function<int(int, int)> returnLamda ()
{
    return [] (int x, int y)
    {
        return x*y;
    };
}

int main()
{
    auto lf = returnLamda();
    std::cout << lf(2,4) <<"\n";
    return 0;
}