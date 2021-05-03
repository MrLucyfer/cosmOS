//
// Created by MrMischief on 02/05/2021.
//

#pragma once
#include <stdint.h>

namespace Kernel{

    struct GDT_Entry {
        uint16_t limit0;
        uint16_t base0;
        uint8_t base1;
        uint8_t access;
        uint8_t limit1_flags;
        uint8_t base2;
    }__attribute__((packed));

    struct GDT_Struct {
        uint16_t size;
        uint64_t offset;
    }__attribute__((packed));

    class GDT {
    public:
        GDT();
        void AddEntry(uint16_t limit0,
                        uint16_t base0,
                        uint8_t base1,
                        uint8_t access,
                        uint8_t limit1_flags,
                        uint8_t base2);
        void LoadGDT();
    private:
        GDT_Entry m_gdt_entry[4]; //We are gonna add 4 entries to the GDT
        GDT_Struct m_lgdt;
        int m_index;
    };
}

