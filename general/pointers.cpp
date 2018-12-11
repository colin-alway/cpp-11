/**
 g++ -std=c++11 pointers.cpp -o pointers
 */
#include <iostream>
#include <string>
#include <memory>   // std::unique_ptr

class Shape {
public:
    Shape()=default;
    virtual ~Shape() {
        std::cerr << "~Shape" << std::endl;
    }
};

class Circle : public Shape {
    int* i_;
public:
    Circle(int i) {
        i_ = new int;
        *i_ = i;
    }
    virtual ~Circle() {
        std::cerr << "~Circle" << std::endl;
        delete i_;
    }
};

std::unique_ptr<Shape> get_shape(std::string& name) {

    return std::unique_ptr<Shape>{new Circle{123}};
}


void func() {
    
    std::string name("spam.txt");
    std::unique_ptr<Shape> shape = get_shape(name);
}


int main() {
    
    std::cerr << "func" << std::endl;
    func();
    std::cerr << "func" << std::endl;
    func();
    std::cerr << "return 0" << std::endl;
    return 0;
}
