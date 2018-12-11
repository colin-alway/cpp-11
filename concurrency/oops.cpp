//! g++ -pthread -std=c++11 oops.cpp -o oops
//!
#include <iostream>
#include <thread>

void do_something(int i)
{
    //sleep(1);
}

struct func
{
    int& i;
    func(int& i_) : i(i_) {}
    void operator() ()
    {
        for (unsigned j=0; j<1000;++j)
        {
            do_something(i);
        }
    }
};

void oops()
{
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main()
{
    oops();
    
    return EXIT_SUCCESS;
}
