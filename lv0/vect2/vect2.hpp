#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

struct vect2 {
    int x, y;

    // Constructors
    vect2(int a = 0, int b = 0) : x(a), y(b) {}

    // Subscript operator (required by subject)
    int &operator[](int i) { return (i == 0) ? x : y; }
    const int &operator[](int i) const { return (i == 0) ? x : y; }

    // Arithmetic with scalar
    vect2 operator+(int i) const { return vect2(x + i, y + i); }
    vect2 operator-(int i) const { return vect2(x - i, y - i); }
    vect2 operator*(int i) const { return vect2(x * i, y * i); }

    // Arithmetic with vector
    vect2 operator+(const vect2 &v) const { return vect2(x + v.x, y + v.y); }
    vect2 operator-(const vect2 &v) const { return vect2(x - v.x, y - v.y); }
    vect2 operator*(const vect2 &v) const { return vect2(x * v.x, y * v.y); }

    // Compound assignment
    vect2 &operator+=(const vect2 &v) { x += v.x; y += v.y; return *this; }
    vect2 &operator-=(const vect2 &v) { x -= v.x; y -= v.y; return *this; }
    vect2 &operator+=(int i) { x += i; y += i; return *this; }
    vect2 &operator-=(int i) { x -= i; y -= i; return *this; }

    // Increment / Decrement
    vect2 &operator++() { x++; y++; return *this; } // prefix
    vect2 operator++(int) { vect2 tmp = *this; ++(*this); return tmp; } // postfix
    vect2 &operator--() { x--; y--; return *this; }
    vect2 operator--(int) { vect2 tmp = *this; --(*this); return tmp; }

    // Comparison
    bool operator==(const vect2 &v) const { return x == v.x && y == v.y; }
    bool operator!=(const vect2 &v) const { return !(*this == v); }
};

// Symmetrical operators (scalar * vect)
inline vect2 operator+(int i, const vect2 &v) { return v + i; }
inline vect2 operator*(int i, const vect2 &v) { return v * i; }

// Output operator (must match subject format)
inline std::ostream &operator<<(std::ostream &s, const vect2 &v) {
    s << "{" << v.x << ", " << v.y << "}" << std::endl; // std::endl is required
    return s;
}

#endif