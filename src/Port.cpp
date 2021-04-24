//
// Created by MrMischief on 24/04/2021.
//

#include "Port.h"

Kernel::Port::Port(uint16_t portNumber) {
    this->portNumber = portNumber;
}

Kernel::Port::~Port() {
}

Kernel::Port8Bit::Port8Bit(uint16_t portNumber):
    Port(portNumber)
{

}

Kernel::Port8Bit::~Port8Bit() {

}

void Kernel::Port8Bit::Write(uint8_t data) {
    __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portNumber));
}

uint8_t Kernel::Port8Bit::Read() {
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd" (portNumber));
    return result;
}

Kernel::Port8BitSlow::Port8BitSlow(uint16_t portNumber):
        Port8Bit(portNumber)
{

}

Kernel::Port8BitSlow::~Port8BitSlow() {

}

void Kernel::Port8BitSlow::Write(uint8_t data) {
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (portNumber));
}

Kernel::Port16Bit::Port16Bit(uint16_t portNumber):
        Port(portNumber)
{

}

Kernel::Port16Bit::~Port16Bit() {

}

void Kernel::Port16Bit::Write(uint16_t data) {
__asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (portNumber));
}

uint16_t Kernel::Port16Bit::Read() {
    uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a"(result) : "Nd" (portNumber));
    return result;
}

Kernel::Port32Bit::Port32Bit(uint16_t portNumber):
Port(portNumber)
        {

        }

Kernel::Port32Bit::~Port32Bit() {

}

void Kernel::Port32Bit::Write(uint32_t data) {
__asm__ volatile("outl %0, %1" : : "a" (data), "Nd" (portNumber));
}

uint32_t Kernel::Port32Bit::Read() {
    uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a"(result) : "Nd" (portNumber));
    return result;
}

