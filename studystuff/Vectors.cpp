#include <iostream>
#include "Vectors.h"

// Constructor
Vector::Vector(float x, float y) : x(x), y(y) {}

// Getters
float Vector::getX() const {
    return x;
}

float Vector::getY() const {
    return y;
}

// Add two vectors
Vector Vector::add(const Vector& other) const {
    return Vector(x + other.x, y + other.y);
}

// Subtract two vectors
Vector Vector::subtract(const Vector& other) const {
    return Vector(x - other.x, y - other.y);
}

// Scale the vector by a scalar
Vector Vector::scale(float scalar) const {
    return Vector(x * scalar, y * scalar);
}

// Display the vector
void Vector::display() const {
    std::cout << "Vector(" << x << ", " << y << ")" << std::endl;
}