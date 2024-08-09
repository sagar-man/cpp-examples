#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

const int MAX = 10;
std::mutex mu;
std::condition_variable cond;
int count = 1;

void printEven()
{
    while (count < MAX)
    {
        std::unique_lock<std::mutex> lock(mu);
        cond.wait(lock, []()
        {
            return (count%2==0);
        });
        std::cout <<"From even: " << count <<"\n";
        count++;
        cond.notify_all();
    }
}

void printOdd()
{
    while (count < MAX)
    {
        std::unique_lock<std::mutex> lock(mu);
        cond.wait(lock, []()
        {
            return (count%2==1);
        });
        std::cout <<"From odd: " << count <<"\n";
        count++;
        cond.notify_all();
    }
}

int main()
{
    std::thread t1(printEven);
    std::thread t2(printOdd);

    t1.join();
    t2.join();

    return 0;
}