#include <iostream>
#include <cstdint>
#include <array>

// 1. Forward Declaration
class Bus; 

// 2. CPU Class
class olc6502 {
public:
    Bus* bus = nullptr;
    void ConnectBus(Bus* n) { bus = n; }
    
    // ลองใส่ฟังก์ชันอ่านเขียนผ่าน Bus
    uint8_t read(uint16_t a);
    void write(uint16_t a, uint8_t d);

    uint8_t a = 0x00;
    void reset() { a = 0x42; }
};

// 3. Bus Class (ยกที่คุณส่งมามาวางตรงนี้)
class Bus {
public:
    Bus() {
        cpu.ConnectBus(this); // เชื่อม CPU เข้ากับ Bus ตัวนี้
        ram.fill(0x00);       // ล้าง RAM ให้สะอาด
    }
    ~Bus() {}

    olc6502 cpu;
    std::array<uint8_t, 64 * 1024> ram;

    void write(uint16_t addr, uint8_t data) {
        if (addr >= 0x0000 && addr <= 0xFFFF) ram[addr] = data;
    }

    uint8_t read(uint16_t addr, bool bReadOnly = false) {
        if (addr >= 0x0000 && addr <= 0xFFFF) return ram[addr];
        return 0x00;
    }
};

// 4. ไส้ในฟังก์ชัน CPU ที่ต้องรอให้รู้จัก Bus ก่อน
uint8_t olc6502::read(uint16_t a) {
    return bus->read(a);
}

void olc6502::write(uint16_t a, uint8_t d) {
    bus->write(a, d);
}

// --- Main สำหรับทดสอบ ---
int main() {
    Bus nes; // สร้างเครื่อง NES ขึ้นมา (มีทั้ง Bus, CPU, RAM)
    
    // ลองเขียนข้อมูลลง RAM ผ่าน Bus
    nes.write(0x0100, 0xFF);
    
    // ลองให้ CPU อ่านข้อมูลจาก RAM
    uint8_t val = nes.cpu.read(0x0100);
    
    std::cout << "Read from RAM via CPU: 0x" << std::hex << (int)val << std::endl;
    if(val == 0xFF) std::cout << "BUS IS WORKING! 55555" << std::endl;

    return 0;
}