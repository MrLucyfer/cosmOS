//
// Created by MrMischief on 02/05/2021.
//

#include "Terminal.h"

Terminal::Terminal(){}

Terminal& Terminal::the() {
    static Terminal instance;
    return instance;
}

void Terminal::SetFramebuffer(Gfx::Framebuffer *framebuffer) {
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
        if(*string == '\n') {
            m_cursorY += FONT_HEIGHT2;
            m_cursorX = 0;
        } else {
            writeChar(*string);
            m_cursorX += FONT_WIDTH2;
        }
        ++string;
    }
}

void Terminal::SetForegroundColor(Gfx::Color color) {
    m_fg = color;
}

void Terminal::SetBackgroundColor(Gfx::Color color) {
    m_bg = color;
}