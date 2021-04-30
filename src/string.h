//
// Created by MrMischief on 30/04/2021.
//
#pragma once

static inline size_t strlen(const char* str) {
    size_t size = 0;
    while(str[size] != '\0') {
        ++size;
    }

    return size;
}
