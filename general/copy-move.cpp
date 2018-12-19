/**
 * if a class has a destructor default copy & move are not created
 */
class Vector {

    Vector(const Vector& a);            // copy constructor
    Vector& operator=(const Vector& a); // copy assignment
    
    Vector(Vector&& a);                 // move constructor
    Vector& operator=(Vector&& a);      // move assignment
};

// move constructor
Vector::Vector(Vector&& a) : elem{a.elem}, sz{a.sz} {
    a.elem = nullptr;
    a.sz = 0
}

Vector vec(int s) {

    Vector res;
    Vector y, z;
    
    y = res;            // copy
    z = std::move(y);   // move
    return res;         // move
}
