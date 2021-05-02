//
// Created by MrMischief on 01/05/2021.
//

#include <stdint.h>
#include <stddef.h>
#include "stivale2.h"
#include "Gfx/Framebuffer.h"
#include "Gfx/Color.h"
#include "Terminal.h"

//Creating a stack for the bootloader
static uint8_t stack[4096];

static struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
        // All tags need to begin with an identifier and a pointer to the next tag.
        .tag = {
                // Identification constant defined in stivale2.h and the specification.
                .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
                // If next is 0, then this marks the end of the linked list of tags.
                .next = 0
        },
        // We set all the framebuffer specifics to 0 as we want the bootloader
        // to pick the best it can.
        .framebuffer_width  = 0,
        .framebuffer_height = 0,
        .framebuffer_bpp    = 0
};

__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr = {
        .entry_point = 0,

        .stack = (uintptr_t)stack + sizeof(stack),
        .flags = 0,
        // This header structure is the root of the linked list of header tags and
        // points to the first one (and in our case, only).
        .tags = (uintptr_t)&framebuffer_hdr_tag
};

void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id) {
    struct stivale2_tag *current_tag = (void *)stivale2_struct->tags;
    for (;;) {
        // If the tag pointer is NULL (end of linked list), we did not find
        // the tag. Return NULL to signal this.
        if (current_tag == NULL) {
            return NULL;
        }

        // Check whether the identifier matches. If it does, return a pointer
        // to the matching tag.
        if (current_tag->identifier == id) {
            return current_tag;
        }

        // Get a pointer to the next tag in the linked list and repeat.
        current_tag = (void *)current_tag->next;
    }
}


extern "C" void _start(struct stivale2_struct *stivale2_struct) {

    struct stivale2_struct_tag_framebuffer* framebuffer_str;
    framebuffer_str = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    if(framebuffer_str == NULL) {
        for(;;) {
            asm("hlt");
        }
    }

    Gfx::Framebuffer screen(framebuffer_str);
    screen.ClearScreen({.r = 0, .g = 0, .b = 0xff});


    for(;;) {
        asm("hlt");
    }
}
