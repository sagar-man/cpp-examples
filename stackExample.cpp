#include <iostream>
#include <stack>

void printStack(std::stack<int> st)
{
    std::stack sp = st;
    while(!sp.empty())
    {
        std::cout <<" " << sp.top();
        sp.pop();
    }
}

int main()
{
    std::stack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);
    st.push(40);

    printStack(st);

    return 0;
}