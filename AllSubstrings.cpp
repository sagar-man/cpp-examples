/*
https://leetcode.com/problems/palindromic-substrings/description/
*/

#include <iostream>
#include <string>
#include <vector>

// O(n^2)
void allSubStr(std::string& str)
{
    int n = str.size();
    for(int i=0; i<n; ++i)
    {
        char temp[n - i + 1];
        int tempIndex = 0;
        for(int j=i; j<n; ++j)
        {
            temp[tempIndex++] = str[j];
            temp[tempIndex] = '\0';
            std::cout << temp <<"\n";
        }
    }
}

int main()
{
    std::string str("abcd");
    allSubStr(str);
    return 0;
}