//
// Created by MrMischief on 27/04/2021.
//

#include "Terminal.h"

Terminal::Terminal() {
    initialize();
}

uint8_t Terminal::vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

uint16_t Terminal::vga_entry(unsigned char ch, uint8_t color) {
    return (uint16_t) ch | (uint16_t) color << 8;
}

void Terminal::initialize(void) {
    ClearScreen();
}

void Terminal::ClearScreen() {
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

void Terminal::setColor(uint8_t color) {
    terminal_color = color;
}

void Terminal::putAt(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void Terminal::putChar(char c) {
    if(c == '\n') {
        terminal_col = 0;
        ++terminal_row;
        return;
    }
    putAt(c, terminal_color, terminal_col, terminal_row);
    if(++terminal_col == VGA_WIDTH) {
        terminal_col = 0;
        if(++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
}

void Terminal::Write(const char* data, size_t size) {
    for(size_t i = 0; i < size; ++i) {
        putChar(data[i]);
    }
}