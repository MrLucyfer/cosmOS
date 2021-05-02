//
// Created by MrMischief on 02/05/2021.
//
#pragma once
#include <stdint.h>
#include "Framebuffer.h"
#include "Color.h"


class Terminal {
public:
    Terminal(Gfx::Framebuffer* framebuffer);
    void Write(const char* string);
private:
    void writeChar(char letter);
    uint16_t m_width;
    uint16_t m_height;
    Gfx::Framebuffer* m_framebuffer;

    uint32_t m_cursorX = 20;
    uint32_t m_cursorY = 0;

    Gfx::Color m_fg = {.r = 0xff, .g = 0xff, .b= 0xff };
    Gfx::Color m_bg = {.r = 0x00, .g = 0x00, .b= 0x00 };;
};
