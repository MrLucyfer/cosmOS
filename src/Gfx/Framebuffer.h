//
// Created by NIL FOLQUER on 2/5/21.
//
#pragma once
#include <stdint.h>
#include "../stivale2.h"
#include "Color.h"

namespace Gfx {

class Framebuffer {
public:
    Framebuffer(struct stivale2_struct_tag_framebuffer* fb_str);

    uint16_t getWidth() const;
    uint16_t getHeight() const;
    uint16_t getBPP() const;

    void ClearScreen(Color col);

private:
    void putPixel(int x, int y, Color col);

private:
    uint8_t* m_address;
    uint16_t m_width;
    uint16_t m_height;
    uint16_t m_bpp;
};
}


