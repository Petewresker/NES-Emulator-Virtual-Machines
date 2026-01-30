#include <iostream>
#include <iomanip>
#include "Bus.h"
#include "olc6502.h"

int main() {
    Bus nes;
    
    std::cout << "--- NES System Connectivity Test ---" << std::endl;

    // 1. ทดสอบการเขียน/อ่าน RAM โดยตรงผ่าน Bus
    nes.write(0x0000, 0xAA);
    uint8_t ram_val = nes.read(0x0000);
    std::cout << "RAM Test (0x0000): " << (ram_val == 0xAA ? "PASS" : "FAIL") 
              << " [Value: 0x" << std::hex << (int)ram_val << "]" << std::endl;

    // 2. ทดสอบว่า CPU เชื่อมกับ Bus หรือยัง
    // จำลองการ Reset (CPU จะไปอ่าน Vector ที่ 0xFFFC-0xFFFD)
    nes.write(0xFFFC, 0x00); // Low byte
    nes.write(0xFFFD, 0x80); // High byte (สรุปคือให้ PC ไปเริ่มที่ 0x8000)
    
    nes.cpu.reset();

    std::cout << "CPU Reset Test (PC): " << (nes.cpu.pc == 0x8000 ? "PASS" : "FAIL") 
              << " [PC: 0x" << std::hex << nes.cpu.pc << "]" << std::endl;
    
    std::cout << "CPU Status Test: 0x" << (int)nes.cpu.status << std::endl;

    return 0;
}