/// 5.3.1 Tasks and threads

#include <thread>

void f(); // function
struct F { // function object
    void operator()(); // F’s call operator (§3.4.3)
};
void user()
{
    thread t1 {f}; // f() executes in separate thread
    thread t2 {F()}; // F()() executes in separate thread
    t1.join(); // wait for t1
    t2.join(); // wait for t2
}

/// bad...
void f() { cout << "Hello "; }
    struct F {
    void operator()() { cout << "Parallel World!\n"; }
};


/// 5.3.2 Passing Arguments


void f(vector<double>& v); // function do something with v
struct F { // function object: do something with v
    vector<double>& v;
    F(vector<double>& vv) :v{vv} { }
    void operator()(); // application operator ; §3.4.3
};
int main()
{
    vector<double> some_vec {1,2,3,4,5,6,7,8,9};
    vector<double> vec2 {10,11,12,13,14};
    thread t1 {f,some_vec}; // f(some_vec) executes in a separate thread
    thread t2 {F{vec2}}; // F(vec2)() executes in a separate thread
    t1.join();
    t2.join();
}


// 5.3.3 Returning Results


void f(const vector<double>& v, double∗ res);// take input from v; place result in *res
class F {
    public:
    F(const vector<double>& vv, double∗ p) :v{vv}, res{p} { }
    void operator()(); // place result in *res

    private:
    const vector<double>& v; // source of input
    double∗ res; // target for output
};

int main()
{
    vector<double> some_vec;
    vector<double> vec2;
    // ...
    double res1;
    double res2;
    thread t1 {f,some_vec,&res1}; // f(some_vec,&res1) executes in a separate thread
    thread t2 {F{vec2,&res2}}; // F{vec2,&res2}() executes in a separate thread
    t1.join();
    t2.join();
    cout << res1 << ' ' << res2 << '\n';
}



/// 5.3.4 Sharing Data

#include <mutex>

mutex m; // controlling mutex
int sh; // shared data
void f()
{
    unique_lock<mutex> lck {m}; // acquire mutex
    sh += 7; // manipulate shared data
} // release mutex implicitly

class Record {
    public:
    mutex rm;
    // ...
};

void f()
{
    // ...
    unique_lock<mutex> lck1 {m1,defer_lock}; // defer_lock: don’t yet try to acquire the mutex
    unique_lock<mutex> lck2 {m2,defer_lock};
    unique_lock<mutex> lck3 {m3,defer_lock};
    // ...
    lock(lck1,lck2,lck3); // acquire all three locks
    // ... manipulate shared data ...
} // implicitly release all mutexes

/// 5.3.4.1 Waiting for Events

#include <chrono>
#include <condition_variable>

using namespace std::chrono;
auto t0 = high_resolution_clock::now();
this_thread::sleep_for(milliseconds{20});
auto t1 = high_resolution_clock::now();
cout << duration_cast<nanoseconds>(t1−t0).count() << " nanoseconds passed\n";

class Message { // object to be communicated
    // ...
};
queue<Message> mqueue; // the queue of messages
condition_variable mcond; // the var iable communicating events
mutex mmutex; // the locking mechanism

void consumer()
{
    while(true) {
    unique_lock<mutex> lck{mmutex}; // acquire mmutex
    while (mcond.wait(lck)) /* do nothing */; // release lck and wait;
    // re-acquire lck upon wakeup
    auto m = mqueue.front(); // get the message
    mqueue.pop();
    lck.unlock(); // release lck
    // ... process m ...
    }
}


void producer()
{
    while(true) {
    Message m;
    // ... fill the message ...
    unique_lock<mutex> lck {mmutex}; // protect operations
    mqueue.push(m);
    mcond.notify_one(); // notify
    } // release lock (at end of scope)
}



/// 5.3.5 Communicating Tasks

#include <future>

X v = fx.get(); // if necessary, wait for the value to get computed

void f(promise<X>& px) // a task: place the result in px
{
    // ...
    try {
        X res;
        // ... compute a value for res ...
        px.set_value(res);
    }
    catch (...) { // oops: couldn’t compute res
        // pass the exception to the future’s thread:
        px.set_exception(current_exception());
    }
}

void g(future<X>& fx) // a task: get the result from fx
{
    // ...
    try {
        X v = fx.g et(); // if necessary, wait for the value to get computed
        // ... use v ...
    }
    catch (...) { // oops: someone couldn’t compute v
        // ... handle error ...
    }
}

/// 5.3.5.2 packaged_task


double accum(double∗ beg, double ∗ end, double init)
// compute the sum of [beg:end) starting with the initial value init
{
    return accumulate(beg,end,init);
}

double comp2(vector<double>& v)
{
    using Task_type = double(double∗,double∗,double); // type of task
    packaged_task<Task_type> pt0 {accum}; // package the task (i.e., accum)
    packaged_task<Task_type> pt1 {accum};
    future<double> f0 {pt0.get_future()}; // get hold of pt0’s future
    future<double> f1 {pt1.get_future()}; // get hold of pt1’s future
    double∗ first = &v[0];
    thread t1 {move(pt0),first,first+v.siz e()/2,0}; // star t a thread for pt0
    thread t2 {move(pt1),first+v.siz e()/2,first+v.siz e(),0}; // star t a thread for pt1
    // ...
    return f0.get()+f1.g et(); // get the results
}

/// 5.3.5.3 async()

double comp4(vector<double>& v)
// spawn many tasks if v is large enough
{
    if (v.siz e()<10000) return accum(v.begin(),v.end(),0.0);
    auto v0 = &v[0];
    auto sz = v.siz e();

    auto f0 = async(accum,v0,v0+sz/4,0.0); // first quarter
    auto f1 = async(accum,v0+sz/4,v0+sz/2,0.0); // second quarter
    auto f2 = async(accum,v0+sz/2,v0+sz∗3/4,0.0); // third quarter
    auto f3 = async(accum,v0+sz∗3/4,v0+sz,0.0); // four th quar ter
    return f0.get()+f1.g et()+f2.get()+f3.get(); // collect and combine the results
}
