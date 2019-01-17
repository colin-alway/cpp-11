/// 5.2.1 unique_ptr and shared_ptr

#include <memory>  // unique_ptr, shared_ptr


void f(int i, int j) // X* vs. unique_ptr<X>
{
    X∗ p = new X; // allocate a new X
    unique_ptr<X> sp {new X}; // allocate a new X and give its pointer to unique_ptr
    // ...

    if (i<99) throw Z{}; // may throw an exception
    if (j<77) return; // may retur n "ear ly"
    p−>do_something(); // may throw an exception
    sp−>do_something(); // may throw an exception
    // ...
    delete p; // destroy *p
}

void f(int i, int j) // use a local var iable
{
    X x;
    // ...
}

unique_ptr<X> make_X(int i)
// make an X and immediately give it to a unique_ptr
{
    // ... check i, etc. ...
    return unique_ptr<X>{new X{i}};
}

void f(shared_ptr<fstream>);
void g(shared_ptr<fstream>);
void user(const string& name, ios_base::openmode mode)
{
    shared_ptr<fstream> fp {new fstream(name ,mode)};
    if (!∗fp) throw No_file{}; // make sure the file was properly opened
    f(fp);
    g(fp);
    // ...
}
