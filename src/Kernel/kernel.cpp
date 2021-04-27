//
// Created by MrMischief on 23/04/2021.
//

#include "../AK/types.h"

#include "GDT.h"
#include "Interrupts.h"

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char ch, uint8_t color) {
    return (uint16_t) ch | (uint16_t) color << 8;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while(str[len] != '\0') {
        ++len;
    }

    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_col;
uint8_t terminal_color;
uint16_t* terminal_buffer;


void terminal_initialize(void) {
    terminal_row = 0;
    terminal_col = 0;
    terminal_color = vga_entry_color(vga_color::VGA_COLOR_LIGHT_GREY, vga_color::VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;

    for(size_t y = 0; y < VGA_HEIGHT; ++y) {
        for(size_t x = 0; x < VGA_WIDTH; ++x) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setColor(uint8_t color) {
    terminal_color = color;
}

void terminal_putAt(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putChar(char c) {
    if(c == '\n') {
        terminal_col = 0;
        ++terminal_row;
        return;
    }
    terminal_putAt(c, terminal_color, terminal_col, terminal_row);
    if(++terminal_col == VGA_WIDTH) {
        terminal_col = 0;
        if(++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
}

void terminalWrite(const char* data, size_t size) {
    for(size_t i = 0; i < size; ++i) {
        terminal_putChar(data[i]);
    }
}


void printf(const char* data) {
    terminalWrite(data, strlen(data));
}

extern "C" void kernelMain(void* multiboot_struct, unsigned int magicNumber) {
    terminal_initialize();
    terminal_setColor(vga_entry_color(vga_color::VGA_COLOR_LIGHT_CYAN, vga_color::VGA_COLOR_BLACK));
    printf("Welcome to cosmOS\n");
    printf("WIP");

    Kernel::GDT gdt;
    InterruptManager interrupts(0x20, &gdt);

    interrupts.Activate();

    while(1);
}