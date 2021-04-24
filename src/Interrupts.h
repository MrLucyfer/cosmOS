//
// Created by MrMischief on 24/04/2021.
//
#pragma once
#include <stdint.h>
#include "Port.h"
#include "GDT.h"



namespace Kernel {
class InterruptManager {

protected:
    struct GateDescriptor {
        uint16_t handlerAddressLowBits;
        uint16_t gdt_codeSegmentSelector;
        uint8_t reserved;
        uint8_t access;
        uint16_t handlerAddressHighBits;
    } __attribute__((packed));

    static GateDescriptor interruptDescriptorTable[256];

    struct InterruptDescriptorTablePointer {
        uint16_t size;
        uint32_t base;
    } __attribute__((packed));

    static void SetInterruptDescriptorTableEntry(
        uint8_t interruptNumber,
        uint16_t gdtCodeSegmentSelectorOffset,
        void(*handler)(),
        uint8_t DescriptorPrivilegeLevel,
        uint8_t DescriptorType
    );

    Kernel::Port8BitSlow picMasterCommand;
    Kernel::Port8BitSlow picMasterData;
    Kernel::Port8BitSlow picSlaveCommand;
    Kernel::Port8BitSlow picSlaveData;

public:
    InterruptManager(Kernel::GDT* gdt);
    ~InterruptManager();

    static uint32_t HandleInterrupt(uint8_t interruptNumber, uint32_t esp);

    void Activate();

    static void IgnoreInterruptRequest();
    static void HandleInterruptRequest0x00();
    static void HandleInterruptRequest0x01();
};

}



