//
// Created by MrMischief on 24/04/2021.
//
#include "Interrupts.h"

void printf(const char* str);

uint32_t Kernel::InterruptManager::HandleInterrupt(uint8_t interruptNumber, uint32_t esp) {

    printf("Interrupt");
    return esp;
}

Kernel::InterruptManager::GateDescriptor Kernel::InterruptManager::interruptDescriptorTable[256];

void Kernel::InterruptManager::SetInterruptDescriptorTableEntry(
        uint8_t interruptNumber,
        uint16_t gdtCodeSegmentSelectorOffset,
        void(*handler)(),
        uint8_t DescriptorPrivilegeLevel,
        uint8_t DescriptorType)
{

    const uint8_t IDT_DESC_PRESENT = 0x80;

    interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].handlerAddressHighBits = (((uint32_t)handler) >> 16) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = gdtCodeSegmentSelectorOffset;
    interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT |  (DescriptorPrivilegeLevel&3 << 5) | DescriptorType;
    interruptDescriptorTable[interruptNumber].reserved = 0;
}

Kernel::InterruptManager::InterruptManager(Kernel::GDT *gdt)
:   picMasterCommand(0x20),
    picMasterData(0x21),
    picSlaveCommand(0xA0),
    picSlaveData(0xA1)
{
    uint16_t CodeSegment = gdt->CodeSegmentSelector();
    const uint8_t IDT_INTERRUPTION_GATE = 0xE;

    for(uint16_t i = 0; i < 256; ++i) {
        SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPTION_GATE);
    }

    SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPTION_GATE);
    SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPTION_GATE);

    picMasterCommand.Write(0x11);
    picSlaveCommand.Write(0x11);

    picMasterData.Write(0x20);
    picSlaveData.Write(0x28);

    picMasterData.Write(0x04);
    picSlaveData.Write(0x02);

    picMasterData.Write(0x01);
    picSlaveData.Write(0x01);

    picMasterData.Write(0x00);
    picSlaveData.Write(0x00);

    InterruptDescriptorTablePointer idt;
    idt.size = 265 * sizeof(GateDescriptor); - 1;
    idt.base = (uint32_t)interruptDescriptorTable;
    asm volatile("lidt %0" : : "m"(idt));

}

void Kernel::InterruptManager::Activate() {
    asm("sti");
}

Kernel::InterruptManager::~InterruptManager() {

}
