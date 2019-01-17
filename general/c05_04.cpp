/// 5.4.1 Time

using namespace std::chrono;
auto t0 = high_resolution_clock::now();
do_work();
auto t1 = high_resolution_clock::now();
cout << duration_cast<milliseconds>(t1−t0).count() << "msec\n";



/// 5.4.2 Type Functions

#include <limits>

constexpr float min = numeric_limits<float>::min(); // smallest positive float (§40.2)

constexpr int szi = sizeof(int); // the number of bytes in an int

/// 5.4.2.1 iterator_traits


void test(vector<string>& v, forward_list<int>& lst)
{
    sort(v); // sor t the vector
    sort(lst); // sor t the singly-linked list
}

template<typename Ran> // for random-access iterators
void sort_helper(Ran beg, Ran end, random_access_iterator_tag) // we can subscript into [beg:end)
{
    sort(beg,end); // just sort it
}

template<typename For> // for forward iterators
void sort_helper(For beg, For end, forward_iterator_tag) // we can traverse [beg:end)
{
    vector<decltype(∗beg)> v {beg,end}; // initialize a vector from [beg:end)
    sort(v.begin(),v.end());
    copy(v.begin(),v.end(),beg); // copy the elements back
}

template<typname C>
void sort(C& c)
{
    using Iter = Iterator_type<C>;
    sort_helper(c.begin(),c.end(),Iterator_category<Iter>{});
}

template<typename C>
using Iterator_type = typename C::iterator; // C’s iterator type
template<typename Iter>
using Iterator_category = typename std::iterator_traits<Iter>::iterator_category; // Iter’s categor y

/// 5.4.2.2 Type Predicates
#include <type_traits>
bool b1 = Is_arithmetic<int>(); // yes, int is an arithmetic type
bool b2 = Is_arithmetic<string>(); // no, std::str ing is not an arithmetic type

template<typename Scalar>
class complex {
    Scalar re, im;
    public:
    static_assert(Is_arithmetic<Scalar>(), "Sorr y, I only suppor t complex of arithmetic types");
    // ...
};

template<typename T>
constexpr bool Is_arithmetic()
{
    return std::is_arithmetic<T>::value ;
}

/// programs that use ::value directly instead of () expose implementation details.

/// 5.4.3 pair and tuple
#include <utility> // std::pair, std::tuple

template<typename Forward_iterator, typename T, typename Compare>
pair<Forward_iterator,Forward_iterator>
equal_range(Forward_iterator first, Forward_iterator last, const T& val, Compare cmp);


auto rec_eq = [](const Record& r1, const Record& r2) { return r1.name<r2.name;};// compare names
void f(const vector<Record>& v) // assume that v is sorted on its "name" field
{
    auto er = equal_range(v.begin(),v.end(),Record{"Reg"},rec_eq);

    for (auto p = er.first; p!=er.second; ++p) // print all equal records
        cout << ∗p; // assume that << is defined for Record
}


void f(vector<string>& v)
{
    auto pp = make_pair(v.begin(),2); // pp is a pair<vector<str ing>::iterator,int>
    // ...
}

tuple<string,int,double> t2("Sild",123, 3.14); // the type is explicitly specified
auto t = make_tuple(string("Herring"),10, 1.23); // the type is deduced
// t is a tuple<str ing,int,double>

string s = get<0>(t); // get first element of tuple
int x = get<1>(t);
double d = get<2>(t);

