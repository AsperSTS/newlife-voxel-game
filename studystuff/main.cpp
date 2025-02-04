#include <iostream>
#include "Vectors.h"

int main() {
    // Create two vectors
    Vector v1(3.0f, 4.0f);
    Vector v2(1.0f, 2.0f);

    // Display the vectors
    std::cout << "Vector 1: ";
    v1.display();
    std::cout << "Vector 2: ";
    v2.display();

    // Add the vectors
    Vector v3 = v1.add(v2);
    std::cout << "Vector 1 + Vector 2: ";
    v3.display();

    // Subtract the vectors
    Vector v4 = v1.subtract(v2);
    std::cout << "Vector 1 - Vector 2: ";
    v4.display();

    // Scale the first vector
    Vector v5 = v1.scale(2.0f);
    std::cout << "Vector 1 scaled by 2: ";
    v5.display();

    return 0;
}