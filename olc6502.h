//olc6502.h
#pragma once

#include <vector>
#include <string>
#include <map>
#include <cstdint>


class Bus;

class olc6502
{
public:
    olc6502();
    ~olc6502();

public:
    // 1. Registers (หัวใจของ CPU)
    uint8_t  a      = 0x00;
    uint8_t  x      = 0x00;
    uint8_t  y      = 0x00;
    uint8_t  stkp   = 0x00;
    uint16_t pc     = 0x0000;
    uint8_t  status = 0x00;
    uint8_t  cycles = 0;

    // 2. Flags Enumeration (ตัวบอกสถานะ)
    enum FLAGS6502
    {
        C = (1 << 0), // Carry
        Z = (1 << 1), // Zero
        I = (1 << 2), // Interrupt Disable
        D = (1 << 3), // Decimal Mode
        B = (1 << 4), // Break
        U = (1 << 5), // Unused
        V = (1 << 6), // Overflow
        N = (1 << 7), // Negative
    };

    // 3. Communications (สะพานเชื่อม)
    void ConnectBus(Bus *n) { bus = n; }
    Bus *bus = nullptr;

    // 4. External Signals (ปุ่มกด/สัญญาณจากภายนอก)
    void reset();
    void clock();

private:
    // 5. Helper Functions (ตัวช่วยภายใน)
    uint8_t read(uint16_t a);
    void    write(uint16_t a, uint8_t d);
    uint8_t fetch();

    // 6. Addressing Modes & Opcodes (จองชื่อไว้ก่อน)
    uint8_t IMP(); uint8_t IMM(); 
    uint8_t ADC(); uint8_t AND(); 
};