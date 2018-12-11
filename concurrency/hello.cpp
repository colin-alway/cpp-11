//! g++ -pthread -std=c++11 hello.cpp -o hello
//!
#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello Concurrently" << std::endl;
}

int main()
{
    std::thread t(hello);
    t.join();
    
    return EXIT_SUCCESS;
}
