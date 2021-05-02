//
// Created by MrMischief on 02/05/2021.
//

#include "Terminal.h"
#include "Glyphs.h"
extern char _binary_font_psf_start;

Terminal::Terminal(Gfx::Framebuffer *framebuffer)
{
    m_framebuffer = framebuffer;
}

void Terminal::writeChar(char letter) {
    if(letter & 0x80) {
        letter = 0;
    }

    int offs = letter * 9;

    for(int _y = 0; _y < 9; ++_y) {
        for(int _x = 0; _x < 7; ++_x) {
            char val = Gfx::glyphs[_y + offs] & (1 << _x);
            m_framebuffer->putPixel(m_cursorX + 0 + (_x << 1), m_cursorY + 0 + (_y << 1), val ? m_fg : m_bg);
            m_framebuffer->putPixel(m_cursorX + 1 + (_x << 1), m_cursorY + 0 + (_y << 1), val ? m_fg : m_bg);
            m_framebuffer->putPixel(m_cursorX + 0 + (_x << 1), m_cursorY + 1 + (_y << 1), val ? m_fg : m_bg);
            m_framebuffer->putPixel(m_cursorX + 1 + (_x << 1), m_cursorY + 1 + (_y << 1), val ? m_fg : m_bg);
        }
    }
}

void Terminal::Write(const char *string) {
    while(*string) {
        if(*string == "\n") {
            m_cursorY += FONT_HEIGHT2;
            m_cursorX = 0;
        } else {
            writeChar(*string);
        }
        ++string;
        if(m_cursorX < m_width) {
            m_cursorX += FONT_WIDTH2;
            if(m_cursorY < m_height) {
                m_cursorY = 0;
            }
        }
    }
}