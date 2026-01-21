#pragma once
#include <string>
#include <algorithm>
#include <iostream>

struct bigint {
    std::string _val;

    // Utility to remove leading zeros, keeping at least one "0" 
    void _trim() {
        size_t first = _val.find_first_not_of('0');
        if (first == std::string::npos) _val = "0";
        else _val.erase(0, first);
    }

    bigint() : _val("0") {}
    bigint(unsigned int i) : _val(std::to_string(i)) {}
    bigint(const std::string& s) : _val(s) { _trim(); }
    bigint(const bigint& o) : _val(o._val) {}
    bigint& operator=(const bigint& o) { _val = o._val; return *this; }

    // Addition logic: reverse strings, add digits with carry 
    bigint operator+(const bigint& o) const {
        std::string a = _val, b = o._val, res = "";
        std::reverse(a.begin(), a.end()); std::reverse(b.begin(), b.end());
        int carry = 0, i = 0;
        while (i < (int)a.size() || i < (int)b.size() || carry) {
            int sum = carry + (i < (int)a.size() ? a[i]-'0' : 0) + (i < (int)b.size() ? b[i]-'0' : 0);
            res += (sum % 10 + '0'); carry = sum / 10; i++;
        }
        std::reverse(res.begin(), res.end());
        return bigint(res);
    }

    // Comparison operators 
    bool operator==(const bigint& o) const { return _val == o._val; }
    bool operator<(const bigint& o) const { 
        return _val.size() != o._val.size() ? _val.size() < o._val.size() : _val < o._val; 
    }
    bool operator>(const bigint& o) const { return o < *this; }
    bool operator<=(const bigint& o) const { return !(*this > o); }
    bool operator>=(const bigint& o) const { return !(*this < o); }
    bool operator!=(const bigint& o) const { return !(*this == o); }

    // Correct digitshift base 10 (42 << 3 = 42000) 
    bigint operator<<(unsigned int n) const {
        if (_val == "0") return *this;
        bigint res(*this);
        res._val.append(n, '0');
        return res;
    }

    // Correct digitshift base 10 (1337 >> 2 = 13) 
    bigint operator>>(unsigned int n) const {
        if (n >= _val.size()) return bigint("0");
        return bigint(_val.substr(0, _val.size() - n));
    }

    // Helpers for the provided main
    unsigned int toUInt() const { return std::stoul(_val); }
    bigint operator<<(const bigint& o) const { return *this << o.toUInt(); }
    bigint operator>>(const bigint& o) const { return *this >> o.toUInt(); }
    bigint& operator+=(const bigint& o) { return *this = *this + o; }
    bigint& operator<<=(unsigned int n) { return *this = *this << n; }
    bigint& operator>>=(unsigned int n) { return *this = *this >> n; }
    bigint operator++(int) { bigint t(*this); *this = *this + 1; return t; }
    bigint& operator++() { return *this = *this + 1; }
};

// Printing 
inline std::ostream& operator<<(std::ostream& os, const bigint& b) { return os << b._val; }