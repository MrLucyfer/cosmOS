//
// Created by MrMischief on 23/04/2021.
//

#include "../AK/types.h"
#include "../AK/stdio.h"
#include "GDT.h"
#include "Terminal.h"
#include "Interrupts.h"

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void kernelMain(void* multiboot_struct, unsigned int magicNumber) {
    Terminal::the().ClearScreen();
    Terminal::the().setColor(Terminal::vga_entry_color(Terminal::VGA_COLOR_WHITE, Terminal::VGA_COLOR_BLACK));
    printf("Welcome to cosmOS\n");
    printf("WIP\n");

    Kernel::GDT gdt;
    InterruptManager interrupts(0x20, &gdt);

    printf("Activating interrupts...");
    interrupts.Activate();


    while(1);
}