//
// Created by NIL FOLQUER on 2/5/21.
//

#pragma once
#include <stdint.h>

namespace Gfx {

    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint32_t getColor() {
          return b | (g << 8) | (r << 16) | 0xff;
        };
    };

}