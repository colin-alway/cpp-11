/// g++ -std=c++11 c04.cpp -o c04.exe
/// p104-105
///
#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;


bool has_c1(const string& s, char c) // does s contain the character c?
{
    auto p = find(s.begin(),s.end(),c);
    if (p!=s.end())
        return true;
    else
        return false;
}


bool has_c2(const string& s, char c) // does s contain the character c?
{
    return find(s.begin(),s.end(),c)!=s.end();
}


vector<string::iterator> find_all(string& s, char c) // find all occurrences of c in s
{
    vector<string::iterator> res;
    for (auto p = s.begin(); p!=s.end(); ++p)
        if (*p==c)
            res.push_back(p);
    return res;
}

/// A generalised find_all():
template<typename C, typename V>
vector<typename C::iterator> find_all(C& c, V v) // find all occurrences of v in c
{
    vector<typename C::iterator> res;
    for (auto p = c.begin(); p!=c.end(); ++p)
        if (*p==v)
            res.push_back(p);
    return res;
}

/// type alias version
/*
template<typename T>
using Iterator<T> = typename T::iterator;

template<typename C, typename V>
vector<Iterator<C>> find_all2(C& c, V v) // find all occurrences of v in c
{
    vector<Iterator<C>> res;
    for (auto p = c.begin(); p!=c.end(); ++p)
        if (*p==v)
            res.push_back(p);
    return res;
}
*/

void test()
{
    cerr << "TEST" << endl;
    
    string m {"Mary had a little lamb"};
    for (auto p : find_all(m,'a'))
        if (*p!='a')
            cerr << "a bug!\n";
    
    list<double> ld {1.1, 2.2, 3.3, 1.1};
    for (auto p : find_all(ld,1.1))
        if (*p!=1.1)
            cerr << "list bug!\n";
    
    cerr << "test" << endl;
}

/// 4.5.3 stream iterators

int page107a()
{
    ∗oo = "Hello, "; // meaning cout<<"Hello, "
    ++oo;
    ∗oo = "world!\n"; // meaning cout<<"wor ld!\n"
}

int page107b()
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
/*
An ifstream is an istream that can be attached to a file, and an ofstream is an ostream that can be
attached to a file. The ostream_iterator’s second argument is used to delimit output values.
Actually, this program is longer than it needs to be. We read the strings into a vector,
*/

/// We used the names ii, eos, and oo only once, so we could further reduce the size of the program:

int page108a()
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
/*
In the examples above, the algorithms have simply built in the action to be done for each ele-
ment of a sequence. However, we often want to make that action a parameter to the algorithm. For

example, the find algorithm (§32.4) provides a convenient way of looking for a specific value. A
more general variant looks for an element that fulfills a specified requirement, a predicate
For example, we might want to search a map for the first value larger than 42. A map allows us to
access its elements as a sequence of (key,value) pairs, so we can search a map<string,int>’s sequence
for a pair<const string,int> where the int is greater than 42:
*/
struct Greater_than {
    int val;
    Greater_than(int v) : val{v} { }
    bool operator()(const pair<string,int>& r) { return r.second>val; }
};

void f(map<string,int>& m)
{
    auto p = find_if(m.begin(),m.end(),Greater_than{42});
    // ...
}

// alternate lambda expression
int cxx = count_if(m.begin(), m.end(), [](const pair<string,int>& r) { return r.second>42; });




int main() {

    test();
    
    return 0;
}
