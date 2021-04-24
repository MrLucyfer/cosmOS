//
// Created by MrMischief on 24/04/2021.
//

#pragma once
#include <stdint.h>

namespace Kernel {

    class GDT {
    public:
        class SegmentDescriptor {
        public:
            SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
            uint32_t Base();
            uint32_t Limit();
        private:
            uint16_t limit_low;
            uint16_t base_low;
            uint8_t base_high;
            uint8_t type;
            uint8_t flags_limit_high;
            uint8_t base_vhi;
        } __attribute__((packed));

        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

    public:
        GDT();
        ~GDT();

        uint16_t CodeSegmentSelector();
        uint16_t DataSegmentSelector();
    private:

    };
}
