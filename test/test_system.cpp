#include <iostream>
#include <iomanip>
#include "../include/Bus.h"
#include "../include/olc6502.h"

using namespace std;

int main() {
    Bus nes;
    
    cout << "--- NES System Connectivity Test ---" << endl;

    // 1. ทดสอบการเขียน/อ่าน RAM โดยตรงผ่าน Bus
    nes.write(0x0000, 0xAA);
    uint8_t ram_val = nes.read(0x0000);
    cout << "RAM Test (0x0000): " << (ram_val == 0xAA ? "PASS" : "FAIL") 
              << " [Value: 0x" << hex << (int)ram_val << "]" << endl;

    // 2. ทดสอบว่า CPU เชื่อมกับ Bus หรือยัง
    // จำลองการ Reset (CPU จะไปอ่าน Vector ที่ 0xFFFC-0xFFFD)
    nes.write(0x8000, 0xAA);
    nes.write(0xFFFC, 0x00); // Low byte
    nes.write(0xFFFD, 0x80); // High byte (สรุปคือให้ PC ไปเริ่มที่ 0x8000)

    nes.cpu.reset();
    
    uint8_t opcode = nes.cpu.read(nes.cpu.pc);
    auto instruction = nes.cpu.lookup[opcode];


    cout << "Instruction Name: " << instruction.name << endl;

    return 0;
}