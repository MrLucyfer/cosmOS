//
// Created by MrMischief on 30/04/2021.
//
#pragma once
#include <stdint.h>
#include "kprintf.h"


typedef struct gdt_ptr{
    uint16_t limit; //Size of GDT
    uint32_t base;  //Pointer to the first entry(NULL one)
}__attribute__((packed));


typedef struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t type : 4;
    uint8_t s    : 1;
    uint8_t dpl  : 2;
    uint8_t limit_high : 4;
    uint8_t l : 1;
    uint8_t d : 1;
    uint8_t g : 1;
    uint8_t base_high;
};