#include <iostream>
// 1 
int main(int argc, const char** argv) {
    std::cout << "Hello, World!" << std::endl;
}


// 2
int main(int argc, const char** argv) {
    std::string str = "aaaaa";
}


// 3 NULL and nullptr
int work(int arg){
    return arg;
}

int work(int* arg){
    return *arg;
}

int main(int argc, const char** argv) {
    int number = work(5);
    int number2 = work(nullptr);        //---- it is defaultly handled to work with pointer at input
}


// 4 strings
class MyString {
    char* buffer = nullptr;
    size_t size = 0;
    size_t reserved = 0;

public:
    MyString() = default;
    MyString(const char* ptr){
        size = strlen(ptr);
        reserved = size + 1;                     // +1 cause of '\0' (ending character)
        buffer = new char[reserved];
        std::copy(ptr, ptr+reserved, buffer);
    };
    MyString(const MyString& str){
        size = str.size;
        reserved = str.size;                     // +1 cause of '\0' (ending character)
        buffer = new char[reserved];
        std::copy(str.buffer, str.buffer+reserved, buffer);
    };
    MyString(MyString&& str){                   // r-value
        size = str.size;
        reserved = str.reserved;
        buffer = str.buffer;
        str.buffer = nullptr;                   // theres 
    };

    MyString& operator=(const MyString& str){
        if(buffer != nullptr){
            delete[] buffer;
        }
        
        size = str.size;
        reserved = str.size;                     // +1 cause of '\0' (ending character)
        buffer = new char[reserved];
        std::copy(str.buffer, str.buffer+reserved, buffer);

        return *this;                           // reference
    };
    MyString& operator=(MyString&& str){
        if(buffer != nullptr){
            delete[] buffer;
        }
        
        size = str.size;
        reserved = str.reserved;
        buffer = str.buffer;
        str.buffer = nullptr; 

        return *this;
    };

    ~MyString(){
        if (buffer != nullptr){
            delete[] buffer;
        }
    }

    char& operator[](const size_t idx){
        return buffer[idx];
    }

    MyString& operator+=(const MyString& str){
        const auto newSize = size + str.size;
        if (reserved < newSize + 1){
            reserved = newSize + 1;
            char* newData = new char[reserved];
            std::copy(buffer, buffer + size + 1, newData);
            delete[] buffer;
            buffer = newData;
        }
        std::copy(str.buffer, str.buffer + str.size, buffer + size);
        size = newSize;

        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const MyString& str){
        if (str.buffer == nullptr){
            return os;
        }
        return os << str.buffer;
    }
};

int main(int argc, const char** argv) {
    std::cout << sizeof(std::string) << std::endl;
};


// 5 namespace
namespace sdl {
    void init();
    void assignWindowName();
    void createWindow(){
        assignWindowName();
    }
    void closeWindow();
}


// 6 typedef
typedef int AircraftId;
using AircraftId = int;