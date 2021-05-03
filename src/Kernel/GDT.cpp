//
// Created by MrMischief on 02/05/2021.
//

#include "GDT.h"
#include <stddef.h>
#include "../Gfx/Terminal.h"

namespace Kernel {
    GDT::GDT(): m_index(0) {

    }

    void GDT::AddEntry(uint16_t limit0, uint16_t base0, uint8_t base1, uint8_t access, uint8_t limit1_flags,
                       uint8_t base2) {
        m_gdt_entry[m_index] = {
            .limit0 = limit0,
            .base0 = base0,
            .base1 = base1,
            .access = access,
            .limit1_flags = limit1_flags,
            .base2 = base2
        };
        m_index++;
    }

    void GDT::LoadGDT() {
        Terminal::the().Write("Loading GDT...\n");
        //Initing the lgdt struct with the GDT size and the address to the first entry
        m_lgdt.size = sizeof(m_gdt_entry) - 1;
        m_lgdt.offset = (size_t) &m_gdt_entry;

        //Loading the table with ASM and the LGDT inst
        asm volatile(
            "lgdt %0"
            :
            //No outputs
            :
            "m" (m_lgdt)
        );
        Terminal::the().Write("GDT Loaded\n");
    }

}