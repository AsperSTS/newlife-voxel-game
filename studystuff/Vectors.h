#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
    float x; // X component
    float y; // Y component

public:
    // Constructor
    Vector(float x = 0.0f, float y = 0.0f);

    // Getters
    float getX() const;
    float getY() const;

    // Operations
    Vector add(const Vector& other) const;
    Vector subtract(const Vector& other) const;
    Vector scale(float scalar) const;

    // Display the vector
    void display() const;
};

#endif // VECTOR_H