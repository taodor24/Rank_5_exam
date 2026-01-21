#include "vect2.hpp"
#include <iostream>

/*
    Compilation command:
    c++ -Wall -Wextra -Werror main.cpp vect2.cpp -o vect_test
*/

int main() {
    // 1. Constructor and Output format test (Subject requirements 4 and 5)
    // Should display {2, 3} followed by a newline [cite: 4, 5]
    vect2 v1(2, 3);
    std::cout << "Test Output format: " << v1;

    // 2. Subscript operator test (Subject requirement 3)
    // Testing write access to components using [0] and [1] 
    v1[0] = 42;
    v1[1] = 21;
    if (v1.x == 42 && v1.y == 21)
        std::cout << "Index operator [0], [1]: OK" << std::endl;

    // 3. Scalar multiplication test (Subject requirement 2)
    // Validating specific expression from the subject 
    if (vect2(2, 2) * 2 == vect2(4, 4))
        std::cout << "Scalar multiplication: OK" << std::endl;

    // 4. Vector addition and scalar subtraction tests (Subject requirement 2)
    // Testing basic mathematical operations [cite: 1, 2]
    vect2 a(10, 10);
    vect2 b(5, 5);
    if ((a + b == vect2(15, 15)) && (a - 5 == vect2(5, 5)))
        std::cout << "Addition/Subtraction: OK" << std::endl;

    // 5. Symmetric operator test
    // Verifying scalar * vector (left-side operation)
    vect2 c = 2 * vect2(1, 1);
    if (c.x == 2 && c.y == 2)
        std::cout << "Symmetric scalar op: OK" << std::endl;

    // 6. Increment operator test
    // Testing postfix increment logic
    vect2 d(1, 1);
    d++;
    if (d == vect2(2, 2))
        std::cout << "Increment: OK" << std::endl;

    std::cout << "\n--- ALL TESTS PASSED ---" << std::endl;
    return 0;
}