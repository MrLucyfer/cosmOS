//
// Created by NIL FOLQUER on 2/5/21.
//

#include "Framebuffer.h"

namespace Gfx {
    Framebuffer::Framebuffer(struct stivale2_struct_tag_framebuffer *fb_str) {
        m_width = fb_str->framebuffer_width;
        m_height = fb_str->framebuffer_height;
        m_bpp = (fb_str->framebuffer_bpp / 8);
        m_pitch = fb_str->framebuffer_pitch;
        m_address = (uint8_t*) fb_str->framebuffer_addr;
    }

    uint16_t Framebuffer::getWidth() const {
        return m_width;
    }
    uint16_t Framebuffer::getHeight() const {
        return m_height;
    }
    uint16_t Framebuffer::getBPP() const {
        return m_bpp;
    }

    void Framebuffer::putPixel(int x, int y, Color col) {
        int index = (x * m_bpp) + (y*m_pitch);
        m_address[index + 0] = col.b;
        m_address[index + 1] = col.g;
        m_address[index + 2] = col.r;
    }

    void Framebuffer::ClearScreen(Color col) {
        for(int y = 0; y < m_height; ++y) {
            for(int x = 0; x < m_width; ++x) {
                putPixel(x, y, col);
            }
        }
    }

}