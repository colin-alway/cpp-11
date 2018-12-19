// functor vs lambda
//
// g++ -std=c++11 functor-vs-lambda.cpp -o functor-vs-lambda.exe
//

#include <algorithm>
#include <iostream>
#include <vector>

// functor for deleting items in a stl container object. example usage:
//
// std::for_each(CONTAINER.begin(), CONTAINER.end(), DeleteObject());
//
struct DeleteObject	{
	template <class T>
	void operator() (T* ptr) const {
        std::cerr << " DeleteObject " << *ptr << std::endl;
		delete ptr;
	}
};

class Object {

    std::vector<int*> data;

public:
    Object() {
        std::cerr << " Object() " << std::endl;
        data.push_back(new int(2));
        data.push_back(new int(3));
        data.push_back(new int(5));
        data.push_back(new int(7));
        data.push_back(new int(11));
    }
    
    ~Object() {
        std::cerr << "~Object() " << std::endl;
        std::for_each(data.begin(), data.end(), DeleteObject());
    }
};

class ObjectLambda {

    std::vector<int*> data;

public:
    ObjectLambda() {
        std::cerr << " ObjectLambda() " << std::endl;
        data.push_back(new int(13));
        data.push_back(new int(17));
        data.push_back(new int(19));
        data.push_back(new int(23));
        data.push_back(new int(27));
    }
    
    ~ObjectLambda() {
        std::cerr << "~ObjectLambda() " << std::endl;
        std::for_each(data.begin(), data.end(), [](int*a){std::cerr << " DeleteLambda " << *a << std::endl; delete a;});
    }
};

int main()
{
    auto object1 = Object();

    auto object2 = ObjectLambda();
    
    return 0;
}
