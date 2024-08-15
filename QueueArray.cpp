#include <iostream>
#include <queue>

void printQue(std::queue<int> & que)
{
    std::queue<int> pq = que;
    while( !pq.empty())
    {
        std::cout <<" " <<pq.front();
        pq.pop();
    }
    std::cout <<"\n";
}

int main()
{
    std::queue<int> que{};
    que.push(10);
    que.push(20);
    que.push(30);
    que.push(40);

    printQue(que);

    std::cout <<"the queue size is: " << que.size();
    std::cout <<"front is: " <<que.front();
    std::cout <<"rear is: "<<que.back();

    

    return 0;
}
