#include <iostream>
#include "UInt.h"

int main() {
    UInt i("000020033351252525235235235423523522222222222221111");
    UInt a1("123");
    UInt a2("333");
    UInt a3("987");
    UInt a4 = a2 + a3;
    std::cout << i.to_string() << "\n";
    std::cout << (a1+a2).to_string() << "\n";
    std::cout << a4.to_string() << "\n";
    return 0;
}