#pragma once
#include <cstdint>
#include <array>
#include "../include/olc6502.h"

class Bus {
public:
    Bus();
    olc6502 cpu; // ตัวเครื่องมีสมอง (CPU) อยู่ข้างใน
    std::array<uint8_t, 64 * 1024> ram;
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool bReadOnly = false);
};