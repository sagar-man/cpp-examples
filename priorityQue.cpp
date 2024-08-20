#include <iostream>
#include <queue>
#include <vector>

int main()
{
    std::vector<int> arr = {10,3,5,15,1};
    
    for(const auto& it : arr)
    {
        std::cout << it <<" ";
    }

    std::priority_queue<int> pq;

    for(int i=0; i<arr.size(); ++i)
    {
        pq.push(arr[i]);
    }
    std::cout <<"\n";

    std::cout <<"priority queue: \n";
    while(!pq.empty())
    {
        std::cout << pq.top() <<" ";
        pq.pop();
    }

}