#include <iostream>
#include <cstring>

class MyString
{
    char* buff;
    size_t len;
    
    public:

    MyString() : buff(nullptr), len(0)
    {
        std::cout <<"Default ctor called\n";
    }

    // parameter ctor
    MyString(const char* src)
    {
        std::cout <<"Parametr ctor called\n";
        if(src)
        {
            len = strlen(src);
            buff = new char[len + 1];
            std::strcpy(buff, src);
        }
        else
        {
            buff = nullptr;
            len = 0;
        }
    }

    void print() const
    {
        std::cout <<"Data: " << buff <<"\n";
    }

    // copy ctor
    MyString(const MyString& src)
    {
        std::cout <<"copy ctor called\n";
        len = src.len;
        buff = new char [len + 1];
        std::strcpy(buff, src.buff);
    }

    // copy assignment
    MyString& operator = (const MyString& src)
    {
        std::cout <<"copy assignment called\n";
        if(this == &src)
        {
            return *this;
        }

        delete[] buff; // clear buff
        len = src.len;
        buff = new char [ len + 1];
        std::strcpy(buff, src.buff);
        return *this;
    }

    // move ctor
    MyString(MyString&& src)
    {
        std::cout <<"move ctor called\n";
        buff = src.buff;
        len = src.len;

        src.buff = nullptr;
        src.len = 0;
    }

    // move assignment
    MyString& operator = (MyString&& src)
    {
        std::cout << "Move assigment called\n";
        if(this == &src)
        {
            return *this;
        }

        delete[] buff;
        buff = src.buff;
        len = src.len;

        src.buff = nullptr;
        src.len = 0;

        return *this;
    }

    ~MyString()
    {
        delete[] buff;
    }
};

int main()
{
    MyString s1, s2("sagar");
    MyString s3(s2), s4; // copy ctor
    s4 = s2; // assignment called

    MyString s5 = std::move(s2); // move ctor
    //s5.print(); // sagar
    //s2.print(); // nothing

    MyString s7("mane"), s8;
    s8 = std::move(s7);
    s8.print();

    return 0;
}

