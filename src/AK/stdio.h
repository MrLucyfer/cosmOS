//
// Created by MrMischief on 27/04/2021.
//

#pragma once
#include "../Kernel/Terminal.h"
#include "String.h"

static inline void printf(const char* data) {
    Terminal::the().Write(data, strlen(data));
}