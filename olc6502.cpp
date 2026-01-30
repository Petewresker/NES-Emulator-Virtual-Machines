#include "olc6502.h"
#include "Bus.h" 

olc6502::olc6502()
{

}

olc6502::~olc6502()
{
}


uint8_t olc6502::read(uint16_t a)
{

    return bus->read(a, false);
}

void olc6502::write(uint16_t a, uint8_t d)
{
    bus->write(a, d);
}

void olc6502::reset()
{
    // อ่านค่าจากตำแหน่ง 0xFFFC (Vector ของ Reset ใน 6502)
    uint16_t lo = read(0xFFFC);
    uint16_t hi = read(0xFFFD);
    pc = (hi << 8) | lo;

    // เคลียร์ค่า Registers พื้นฐาน
    a = 0; x = 0; y = 0;
    stkp = 0xFD;
    status = 0x00 | U; // เซต flag Unused เป็น 1 เสมอ

    cycles = 8; // Reset ใช้เวลา 8 cycles
}