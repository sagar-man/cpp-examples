#include <iostream>
#include <string>

int main() 
{
    std::string str = "123456789";  // Example string
    size_t index = 2;  // Start from the 3rd character (index 2)

    while (index < str.length()) 
    {
        str.erase(index, 1);  // Remove the character at the current index
        // After erasing, the next character to remove will be at index + 2
        index += 2;
    }

    std::cout << "Modified string: " << str << std::endl;

    return 0;
}
