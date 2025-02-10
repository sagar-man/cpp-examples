#include <iostream>
#include <atomic>
#include <mutex>

using namespace std;

template<typename T>
class SharedPtr
{
private:
	T* res;
	std::atomic<int>* counter;
	mutable std::mutex mtx; // Mutex for thread safety

	void incrementCnt()
	{
		if (counter)
		{
			counter->fetch_add(1, std::memory_order_relaxed);
		}
	}

	void decrementCnt()
	{
		if (counter)
		{
			if (counter->fetch_sub(1, std::memory_order_acq_rel) == 1)
			{
				std::lock_guard<std::mutex> lock(mtx); // Lock before deletion
				delete res;
				delete counter;
				res = nullptr;
				counter = nullptr;
			}
		}
	}

public:
	// Constructor
	explicit SharedPtr(T* ptr = nullptr) : res(ptr), counter(ptr ? new std::atomic<int>(1) : nullptr)
	{
		cout << "ctor called\n";
	}

	// Copy Constructor
	SharedPtr(const SharedPtr& ptr)
	{
		std::lock_guard<std::mutex> lock(ptr.mtx);
		res = ptr.res;
		counter = ptr.counter;
		incrementCnt();
	}

	// Copy Assignment
	SharedPtr& operator=(const SharedPtr& ptr)
	{
		if (this != &ptr) // Fix: Compare addresses
		{
			decrementCnt();
			std::lock_guard<std::mutex> lock(ptr.mtx);
			res = ptr.res;
			counter = ptr.counter;
			incrementCnt();
		}
		return *this;
	}

	// Move Constructor
	SharedPtr(SharedPtr&& ptr) noexcept
	{
		std::lock_guard<std::mutex> lock(ptr.mtx);
		res = ptr.res;
		counter = ptr.counter;
		ptr.res = nullptr;
		ptr.counter = nullptr;
	}

	// Move Assignment
	SharedPtr& operator=(SharedPtr&& ptr) noexcept
	{
		if (this != &ptr) // Fix: Compare addresses
		{
			decrementCnt();
			std::lock_guard<std::mutex> lock(ptr.mtx);
			res = ptr.res;
			counter = ptr.counter;
			ptr.res = nullptr;
			ptr.counter = nullptr;
		}
		return *this;
	}

	// Reset function
	void reset(T* ptr = nullptr)
	{
		decrementCnt();
		std::lock_guard<std::mutex> lock(mtx);
		res = ptr;
		counter = ptr ? new std::atomic<int>(1) : nullptr;
	}

	// Get reference count
	int get_count() const
	{
		std::lock_guard<std::mutex> lock(mtx);
		return counter ? counter->load(std::memory_order_relaxed) : 0;
	}

	// Overloaded Operators
	T* operator->() const
	{
		return res;
	}

	T& operator*() const
	{
		return *res;
	}

	T* get() const
	{
		return res;
	}

	// Destructor
	~SharedPtr()
	{
		decrementCnt();
	}
};

// Test Program with Threads
#include <thread>

void testFunction(SharedPtr<int> ptr)
{
	cout << "Thread: " << std::this_thread::get_id() << ", Count: " << ptr.get_count() << endl;
}

int main()
{
	SharedPtr<int> ptr(new int(10));

	std::thread t1(testFunction, ptr);
	std::thread t2(testFunction, ptr);
	std::thread t3(testFunction, ptr);

	t1.join();
	t2.join();
	t3.join();

	cout << "Main Count: " << ptr.get_count() << endl;

	return 0;
}
