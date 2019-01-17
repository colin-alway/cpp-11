// g++ -std=c++11 async.cpp -o async.exe
// Section 5.3.5.3 async()


#include <numeric>  // std::accumulate
#include <future>   // std::async
#include <vector>   // std::vector


using namespace std;

double accum(double* beg, double* end, double init)
// compute the sum of [beg:end) starting with the initial value init
{
    return accumulate(beg,end,init);
}


double comp4(vector<double>& v)
// spawn many tasks if v is large enough
{
    if (v.size()<10000) return accum(&*v.begin(), &*v.end(),0.0);
    auto v0 = &v[0];
    auto sz = v.size();

    auto f0 = async(accum,v0,        v0+sz/4,0.0);      // first quarter
    auto f1 = async(accum,v0+sz/4,   v0+sz/2,0.0);      // second quarter
    auto f2 = async(accum,v0+sz/2,   v0+sz*3/4,0.0);    // third quarter
    auto f3 = async(accum,v0+sz*3/4, v0+sz,0.0);        // fourth quarter
    
    return f0.get() + f1.get() + f2.get() + f3.get();   // collect and combine the results
}


int main()
{
    return 0;
}
