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

class Int;
Int operator-(const Int &x, const Int &y);
Int operator+(const Int &x, const Int &y);
Int operator*(const Int &x, const Int &y);
Int operator*(const Int &x, int y);
Int power10(uint32_t power);

class Int {
private:
    int32_t sign_ = 1;
    vector<int32_t> digits_;
    void pop_zeros(Int &x) {
        while (x.digits_.back() == 0 && x.digits_.size() > 1) {
            x.digits_.pop_back();
        }
    }
public:
    Int(string rep) {
        vector<int32_t> tmp;
        uint32_t pos = 0;
        if (rep[0] == '-') {
            sign_ = -1;
            pos = 1;
        }
        for (auto i = pos; i < rep.length(); ++i) {
            if (isdigit(rep[i])) {
                tmp.push_back(rep[i] - '0');
            }
        }
        digits_ = vector<int32_t>(tmp.crbegin(), tmp.crend());
        pop_zeros(*this);
    }

    Int(const vector<int32_t> &vec, int32_t sign = 1): sign_(sign), digits_(vec) {
        pop_zeros(*this);
    }

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

    string to_raw_string() {
        string ret;
        if (sign_ == -1) {
            ret.reserve(digits_.size()+1);
            ret += "-";
        } else {
            ret.reserve(digits_.size());
        }

        for (auto d = digits_.crbegin(); d != digits_.crend(); ++d) {
            ret += *d + '0';
        }
        return ret;
    }

    bool operator==(const Int &x) const {
        if (sign_ * x.sign_ < 0) return false;
        return digits_ == x.digits_;
    }

    bool operator>(const Int &x) const {
        if (sign_ > 0 && x.sign_ < 0) return true;
        if (sign_ < 0 && x.sign_ > 0) return false;
        if (sign_ < 0 && digits_.size() < x.digits_.size()) return true;
        if (sign_ < 0 && digits_.size() > x.digits_.size()) return false;
        if (sign_ > 0 && digits_.size() < x.digits_.size()) return false;
        if (sign_ > 0 && digits_.size() > x.digits_.size()) return true;
        auto b1 = digits_.crbegin();
        auto e1 = digits_.crend();
        auto b2 = x.digits_.crbegin();
        while (b1 != e1 && *b1 == *b2) {
            ++b1;
            ++b2;
        }
        return sign_ > 0 ? *b1 > *b2 : *b1 < *b2;
    }

    bool operator<(const Int &x) const {
        return !(*this > x) && !(*this == x);
    }

    Int & operator-=(const Int &x) {
        if (x.sign_ < 0) return *this += -x;
        if (x > *this) {
            *this = -(x - *this);
            pop_zeros(*this);
            return *this;
        }
        auto max = std::max(digits_.size(), x.digits_.size());
        digits_.resize(max+1, 0);
        Int xx = x;
        xx.digits_.resize(max, 0);
        for (int i = 0; i < max; ++i) {
            digits_[i] -= xx.digits_[i];
        }
        for (int i = 0; i < max-1; ++i) {
            if (digits_[i] < 0) {
                digits_[i] += 10;
                digits_[i+1] -= 1;
            }
        }
        if (digits_.back() < 0) {
            digits_.back() *= -1;
            sign_ = -1;
        }
        pop_zeros(*this);
        return *this;
    }

    Int & operator+=(const Int &x) {
        auto max = std::max(digits_.size(), x.digits_.size());
        digits_.resize(max+1, 0);
        Int xx = x;
        xx.digits_.resize(max, 0);
        int carry = 0;
        for (int i = 0; i < max; ++i) {
            int sum = digits_[i] + xx.digits_[i] + carry;
            carry = sum / 10;
            digits_[i] = sum % 10;
        }
        if (carry > 0) {
            digits_.back() = carry;
        }
        pop_zeros(*this);
        return *this;
    }

    Int & operator*=(const Int &x) {
        Int origin = *this;
        *this = Int("0");
        for (auto d = x.digits_.crbegin(); d != x.digits_.crend(); ++d) {
            *this *= 10;
            *this += origin * *d;
        }
        pop_zeros(*this);
        return *this;
    }

    Int & operator*=(int x) {
        // 0 <= x <= 10
        if (x == 10) {
            digits_.insert(digits_.begin(), 0);
            return *this;
        }
        digits_.resize(digits_.size()+1, 0);
        int carry = 0;
        for (int i = 0; i < digits_.size(); ++i) {
            int product = digits_[i] * x + carry;
            carry = product / 10;
            digits_[i] = product % 10;
        }
        if (carry > 0) {
            digits_.back() = carry;
        }
        pop_zeros(*this);
        return *this;
    }

    Int operator-() const {
        return Int(digits_, -sign_);
    }

    friend Int karatsuba(const Int &x, const Int &y);
};

Int operator-(const Int &x, const Int &y) {
    Int ret = x;
    ret -= y;
    return ret;
}

Int operator+(const Int &x, const Int &y) {
    Int ret = x;
    ret += y;
    return ret;
}

Int operator*(const Int &x, const Int &y) {
    Int ret = x;
    ret *= y;
    return ret;
}

Int operator*(const Int &x, int y) {
    Int ret = x;
    ret *= y;
    return ret;
}

Int karatsuba(const Int &x, const Int &y) {
    auto size = std::max(x.digits_.size(), y.digits_.size());
    Int xx = x;
    Int yy = y;
    xx.digits_.resize(size);
    yy.digits_.resize(size);

    if (size <= 2) {
        return x * y;
    }

    auto p = size / 2;
    Int xl(vector<int32_t>(xx.digits_.cbegin(), xx.digits_.cbegin()+p));
    Int xh(vector<int32_t>(xx.digits_.cbegin()+p, xx.digits_.cend()));
    Int yl(vector<int32_t>(yy.digits_.cbegin(), yy.digits_.cbegin()+p));
    Int yh(vector<int32_t>(yy.digits_.cbegin()+p, yy.digits_.cend()));
    Int xhyh = karatsuba(xh, yh);
    Int xlyl = karatsuba(xl, yl);
    Int P = karatsuba(xh+xl, yh+yl);
    Int part1 = xhyh * power10(2*p);
    Int part2 = (P - xhyh - xlyl) * power10(p);
    return part1 + part2 + xlyl;
}

Int power10(uint32_t power) {
    vector<int32_t> x(power+1, 0);
    x.back() = 1;
    return x;
}

#endif //KARATSUBA_INT_H
