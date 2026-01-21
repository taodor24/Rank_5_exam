#include <iostream>
#include <cassert>
#include "bigint.hpp"


/*

to test:

c++ -Wall -Wextra -Werror main.cpp bigint.cpp -o bigint_test
./bigint_test



*/


int main() {
    // 1. Test for leading zeros (Requirement)
    bigint b1("000123");
    std::cout << "Leading zeros test (000123): " << b1 << " (Expected: 123)" << std::endl;
    if (b1._val != "123") std::cout << "--- FAIL: Leading zeros not removed!" << std::endl;

    // 2. Addition test (Requirement)
    bigint b2("999");
    bigint b3("1");
    bigint sum = b2 + b3;
    std::cout << "Addition test (999 + 1): " << sum << " (Expected: 1000)" << std::endl;

    // 3. Digit shift to the left test (Requirement)
    // 42 << 3 should be 42000
    bigint b4("42");
    bigint shiftLeft = b4 << 3;
    std::cout << "Shift Left test (42 << 3): " << shiftLeft << " (Expected: 42000)" << std::endl;

    // 4. Digit shift to the right test (Requirement)
    // 1337 >> 2 should be 13
    bigint b5("1337");
    bigint shiftRight = b5 >> 2;
    std::cout << "Shift Right test (1337 >> 2): " << shiftRight << " (Expected: 13)" << std::endl;

    // 5. Zero shift test (Edge case)
    bigint zero("0");
    std::cout << "Zero shift left: " << (zero << 5) << " (Expected: 0)" << std::endl;
    
    // 6. Right shift greater than the number length
    bigint b6("10");
    std::cout << "Shift Right > length: " << (b6 >> 5) << " (Expected: 0)" << std::endl;

    // 7. Comparison test (Requirement)
    bigint c1("100"), c2("20");
    std::cout << "Comparison (100 > 20): " << (c1 > c2 ? "OK" : "FAIL") << std::endl;

    return 0;
}

