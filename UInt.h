//
// Created by Roger on 9/29/2016.
//

#ifndef KARATSUBA_INT_H
#define KARATSUBA_INT_H

#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
using std::string;
using std::vector;

class UInt {
private:
    vector<int32_t> digits_;
public:
    UInt(string rep) {
        vector<int32_t> tmp;
        for (auto i = 0; i < rep.length(); ++i) {
            if (isdigit(rep[i])) {
                tmp.push_back(rep[i] - '0');
            }
        }
        digits_ = vector<int32_t>(tmp.crbegin(), tmp.crend());
    }
    UInt(const vector<int32_t> &vec): digits_(vec) {}

    string to_string() {
        string ret;
        ret.reserve(digits_.size());
        bool is_leading_zero = true;
        for (auto d = digits_.crbegin(); d != digits_.crend(); ++d) {
            if (*d == 0 && is_leading_zero) continue;
            is_leading_zero = false;
            ret += *d + '0';
        }
        return ret;
    }

    friend UInt operator+(const UInt &, const UInt &);
    friend UInt operator*(const UInt &, const UInt &);
};

UInt operator+(const UInt &x, const UInt &y) {
    auto p = std::minmax(x.digits_.size(), y.digits_.size());
    auto max = p.first;
    auto min = p.second;
    vector<int32_t> tmp(max+1, 0);
    int curry = 0;
    for (int i = 0; i < min; ++i) {
        tmp[i] = (x.digits_[i] + y.digits_[i] + curry) % 10;
        if (x.digits_[i] + y.digits_[i] > 10) {
            curry = 1;
        } else {
            curry = 0;
        }
    }
    if (curry == 1) {
        tmp.back() = 1;
    }
    return UInt(std::move(tmp));
}

#endif //KARATSUBA_INT_H
