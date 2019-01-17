/// 4.5.3 Stream Iterators

ostream_iterator<string> oo {cout}; // write str ings to cout

int main()
{
    ∗oo = "Hello, "; // meaning cout<<"Hello, "
    ++oo;
    ∗oo = "world!\n"; // meaning cout<<"wor ld!\n"
}

int main()
{
    string from, to;
    cin >> from >> to; // get source and target file names
    ifstream is {from}; // input stream for file "from"
    istream_iterator<string> ii {is}; // input iterator for stream
    istream_iterator<string> eos {}; // input sentinel
    ofstream os{to}; // output stream for file "to"
    ostream_iterator<string> oo {os,"\n"}; // output iterator for stream
    vector<string> b {ii,eos}; // b is a vector initialized from input [ii:eos)
    sort(b.begin(),b.end()); // sor t the buffer
    unique_copy(b.begin(),b.end(),oo); // copy buffer to output, discard replicated values
    return !is.eof() || !os; // return error state (§2.2.1, §38.3)
}

set<string> b {ii,eos}; // collect strings from input
copy(b.begin(),b.end(),oo); // copy buffer to output

// we could further reduce the size of the program:
int main()
{
    string from, to;
    cin >> from >> to; // get source and target file names
    ifstream is {from}; // input stream for file "from"
    ofstream os {to}; // output stream for file "to"
    set<string> b {istream_iterator<string>{is},istream_iterator<string>{}}; // read input
    copy(b.begin(),b.end(),ostream_iterator<string>{os,"\n"}); // copy to output
    return !is.eof() || !os; // return error state (§2.2.1, §38.3)
}



/// 4.5.4 Predicates


void f(map<string,int>& m)
{
    auto p = find_if(m.begin(),m.end(),Greater_than{42});
    // ...
}

struct Greater_than {
    int val;
    Greater_than(int v) : val{v} { }
    bool operator()(const pair<string,int>& r) { return r.second>val; }
};

int cxx = count_if(m.begin(), m.end(), [](const pair<string,int>& r) { return r.second>42; });



/// 4.5.5 Algorithm Overview

#include <algorithm>


/// Selected Standard Algorithms
//~ p=find(b,e,x) p is the first p in [b:e) so that ∗p==x
//~ p=find_if(b,e,f) p is the first p in [b:e) so that f(∗p)==true
//~ n=count(b,e,x) n is the number of elements ∗q in [b:e) so that ∗q==x
//~ n=count_if(b,e,f) n is the number of elements ∗q in [b:e) so that f(∗q,x)
//~ replace(b,e,v,v2) Replace elements ∗q in [b:e) so that ∗q==v by v2
//~ replace_if(b,e,f,v2) Replace elements ∗q in [b:e) so that f(∗q) by v2
//~ p=copy(b,e ,out) Copy [b:e) to [out:p)
//~ p=copy_if(b,e ,out,f) Copy elements ∗q from [b:e) so that f(∗q) to [out:p)
//~ p=unique_copy(b,e ,out) Copy [b:e) to [out:p); don’t copy adjacent duplicates
//~ sort(b,e) Sort elements of [b:e) using < as the sorting criterion
//~ sort(b,e,f) Sort elements of [b:e) using f as the sorting criterion
//~ (p1,p2)=equal_range(b,e,v) [p1:p2) is the subsequence of the sorted sequence [b:e)
//~ with the value v; basically a binary search for v
//~ p=merge(b,e ,b2,e2,out) Merge two sorted sequences [b:e) and [b2:e2) into [out:p)



/// 4.5.6 Container Algorithms

sort(v.begin(),v.end());

namespace Estd {
    using namespace std;
    template<class C>
    void sort(C& c)
    {
        sort(c.begin(),c.end());
    }

    template<class C, class Pred>
    void sort(C& c, Pred p)
    {
        sort(c.begin(),c.end(),p);
    }
    // ...
}
/// extended std, Estd
