#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

class Singleton
{

protected:
    Singleton(const std::string _value) : value_(_value) { }
    static Singleton* instance_;
    static std::mutex mu_;
    std::string value_;
    
public:
    // not copiybale
    Singleton(const Singleton&) = delete;
    // not assignable
    void operator = (const Singleton&) = delete;

    static Singleton* getInstance(const std::string& _value);

    std::string getValue() const
    {
        return value_;
    }
};

Singleton* Singleton::instance_ = nullptr;

Singleton* Singleton::getInstance(const std::string& _value)
{
    std::lock_guard<std::mutex> lock(mu_);
    if(instance_ == nullptr)
    {
        instance_ = new Singleton(_value);
    }

    return instance_;
}

void ThreadFoo()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Singleton* instance = Singleton::getInstance("Foo");
    std::cout << instance->getValue() <<" \n";

    Singleton* instance2 = Singleton::getInstance("BAR");
    std::cout << instance2->getValue() <<" \n"; // FOO
}

int main()
{
    std::thread t1(ThreadFoo);
    t1.join();

    return 0;
}