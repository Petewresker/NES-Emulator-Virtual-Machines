#pragma once
#include <cstdint>
#include <array>

class Bus {
public:
    Bus();
    std::array<uint8_t, 64 * 1024> ram;
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);
};