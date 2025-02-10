// Non thread safe impl

#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class SharedPtr
{
private:
	T* res;
	int* counter;	

	void incrementCnt()
	{
		if (counter)
		{
			(*counter)++;
		}
	}

	void decrementCnt()
	{
		if (counter)
		{
			(*counter)--;
			if ((*counter) == 0)
			{
				delete res;
				delete counter;
				res = nullptr;
				counter = nullptr;
			}
		}
	}

public:
	// Constructor
	SharedPtr(T* ptr = nullptr) : res(ptr), counter(ptr ? new int(1) : nullptr)
	{
		cout << "ctor called\n";
	}

	// Copy Constructor
	SharedPtr(const SharedPtr& ptr) : res(ptr.res), counter(ptr.counter)
	{
		incrementCnt();
	}

	// Copy Assignment
	SharedPtr& operator=(const SharedPtr& ptr)
	{
		if (this != &ptr) // Fix: Compare addresses
		{
			decrementCnt();
			res = ptr.res;
			counter = ptr.counter;
			incrementCnt();
		}
		return *this;
	}

	// Move Constructor
	SharedPtr(SharedPtr&& ptr) noexcept : res(ptr.res), counter(ptr.counter)
	{
		ptr.res = nullptr;
		ptr.counter = nullptr;
	}

	// Move Assignment
	SharedPtr& operator=(SharedPtr&& ptr) noexcept
	{
		if (this != &ptr) // Fix: Compare addresses
		{
			decrementCnt();
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
		res = ptr;
		counter = ptr ? new int(1) : nullptr;
	}

	// Get reference count
	int get_count() const
	{
		return counter ? *counter : 0;
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

// Test Program
int main()
{
	SharedPtr<int> ptr1; // Default ctor
	SharedPtr<int> ptr2(new int(10)); // Param constructor
	SharedPtr<int> ptr3(ptr2); // Copy ctor
	ptr3 = ptr2; // Copy assignment
	SharedPtr<int> ptr4(std::move(ptr1)); // Move ctor
	ptr2 = std::move(ptr3); // Move assignment

	ptr1.reset(new int(5)); // Reset with new value
	std::cout << (*ptr1) << endl; // * operator
	std::cout << "Count: " << ptr1.get_count() << endl; // Get reference count

	return 0; // Destructor gets called automatically
}
