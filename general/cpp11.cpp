/*
 * g++ -std=c++11 cpp11.cpp -o cpp11
 * g++ -std=c++0x cpp11.cpp -o cpp11
 * 
 * http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html
 * http://stackoverflow.com/questions/3106110/what-are-move-semantics
 * 
 * http://en.cppreference.com/w/cpp/language/lambda
 * 
 */
#include <cmath>
#include <algorithm>    
#include <vector>       // std::vector
#include <iostream>       // std::out

float result(float data)
{
    return data * data - 2.0 * data - 2.0;
}

int main()
{
    auto data = result( 2.0 );
    std::cout << "data " << data << std::endl;
    
    std::vector<int> my_array = {1,2,3,4};
    
    for (auto ii = my_array.begin(); ii != my_array.end(); ++ii)
        std::cout << "1 my_array " << *ii << std::endl;
    
    for (auto ii : my_array)
        std::cout << "2 my_array " << ii << std::endl;
    
    return 0;
}
