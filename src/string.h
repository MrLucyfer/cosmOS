//
// Created by MrMischief on 01/05/2021.
//

#pragma once

static inline size_t strlen(const char* string) {
    size_t length = 0;
    while(string[length] != "\0") {
        ++length;
    }
    return length;
}