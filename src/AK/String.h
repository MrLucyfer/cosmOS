//
// Created by MrMischief on 27/04/2021.
//

#pragma once

static inline size_t strlen(const char* str) {
    size_t len = 0;
    while(str[len] != '\0') {
        ++len;
    }

    return len;
}