#include <iostream>
#include <chrono>
#include <cassert>
#include "Int.h"


int main() {
    vector<int> lengths = {250, 500, 1000, 2000, 4000, 8000, 16000};
    for (auto length : lengths) {
        string xstr;
        xstr.reserve(length+1);
        xstr += "1";
        for (int i = 0; i < length; ++i) {
            xstr += (rand() % 10) + '0';
        }
        Int x(xstr);
        std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
        Int y1 = karatsuba(x, x);
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        Int y2 = x * x;
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        assert(y1 == y2);
        std::cout << "karatsuba uses " << (std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0)).count() << "\n";
        std::cout << "grade school uses " << (std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1)).count() << "\n";
    }
    return 0;
}