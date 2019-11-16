#include <stddef.h>
#include <stdint.h>

#include "colours.h"

// Force cross-compiling
#if defined(__linux__)
    #error "Must compile in a cross compiler"
#elif !defined(__i386__)
    #error "Must be compiler witha x86-elf compiler"
#endif

// x86 VGA textmode buffer
volatile uint16_t *vga_buffer = (uint16_t*)0xB8000;
// Default size of VGA texmode buffer
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

// Variables for holding current row and collumn of the terminal
int term_col = 0;
int term_row = 0;
uint8_t term_colour = 0x0F; // Black bg, white fg

// Initiate terminal by clearing it
void term_init()
{
    // Clear the textmode buffer
    for (int col = 0; col < VGA_COLS; ++col)
    {
        for (int row = 0; row < VGA_ROWS; ++row)
        {
            const size_t index = (VGA_COLS * row) + col;

            // Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC, where:
            // - B is the background colour
            // - F is the foreground coluor
            // - C is the ASCII character
            vga_buffer[index] = ((uint16_t) term_colour << 8) | ' '; // Set current index to blank
        }
    }
}

void text_colour(uint8_t bg, uint8_t fg)
{
    term_colour = (bg << 4) | (fg & 0x0F);
}

void term_putc(char c)
{
    switch (c)
    {
        case '\n': // reset column to 0, ++ the row
        {
            term_col = 0;
            ++term_row;
            break;
        }
        default:
        {
            const size_t index = (VGA_COLS * term_row) + term_col;
            vga_buffer[index] = ((uint16_t) term_colour << 8) | c;
            ++term_col;
            break;
        }
    }
    // If we go past the vga_buffer, reset the term_col an term_row
    if (term_col >= VGA_COLS)
    {
        term_col = 0;
        ++term_row;
    }
    if (term_row >= VGA_ROWS)
    {
        term_col = 0;
        term_row = 0;
    }
}

void term_print(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; ++i)
        term_putc(str[i]);
}

// Entry point
void kernel_main()
{
    // Init Terminal
    text_colour(Black, LightRed);
    term_init();

    // Display Logo
    term_print("\n");
    term_print(".--       .-..-.\n");
    term_print("|-.-..-.-,| |`-.\n");
    term_print("' '  `-''-`-'`-'\n");
    term_print("\n");

    // Display Greeter
    text_colour(Black, White);
    term_print("Welcome to your own x86-elf Kernel\n");
}