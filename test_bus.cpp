#include <iostream>
#include "Bus.h"

int main() {
    Bus b;
    b.write(0x1234, 0xAB);
    if (b.read(0x1234) == 0xAB) {
        std::cout << "Bus Link Success! 5555" << std::endl;
    }
    return 0;
}