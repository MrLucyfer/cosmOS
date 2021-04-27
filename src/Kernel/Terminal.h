//
// Created by MrMischief on 27/04/2021.
//
#pragma once
#include "../AK/types.h"

class Terminal {
public:
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

    static Terminal& the() {
        static Terminal instance;
        return instance;
    }

    static const size_t VGA_WIDTH = 80;
    static const size_t VGA_HEIGHT = 25;
    static uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
    static uint16_t vga_entry(unsigned char ch, uint8_t color);

    void ClearScreen();
    void setColor(uint8_t color);
    void Write(const char* data, size_t size);

    Terminal(Terminal const&)        = delete;
    void operator=(Terminal const&)  = delete;

private:
    Terminal();
    void putAt(char c, uint8_t color, size_t x, size_t y);
    void putChar(char c);
    void initialize(void);
    size_t terminal_row;
    size_t terminal_col;
    uint8_t terminal_color;
    uint16_t* terminal_buffer;

};
