/*compiler-included headers you can freely use:
stdbool.h - for bool
stddef.h - for size_t
stdint.h - for the intX_t and uintX_t
float.h
iso646.h
limits.h
stdarg.h
+ a few more special use GCC headers
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "inc/keyboard.h"

#ifdef __linux__
#error "you're trying to compile for linux, however you should use a crosscompiler instead"
#endif

#ifndef __i386__
#error "this needs to be compiled with a ix86-elf compiler"
#endif


/* Hardware text mode color constants */
enum vga_color
{
    VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

//foregorund & background colors
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

/* size of string */
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_init(void){
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*)0xB8000; //location where the terminal buffer starts
    for(size_t y = 0; y < VGA_HEIGHT; y++){
        for(size_t x = 0; x < VGA_WIDTH; x++){
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}


void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
    if(c != '\n'){
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    }else{
        terminal_column = VGA_WIDTH-1; //this will trigger the "line overflow"
    }
    
    //line overflow
    if(++terminal_column == VGA_WIDTH){
        terminal_column = 0;
        if(++terminal_row == VGA_HEIGHT){
            terminal_row--;
            for(size_t y = 0; y < VGA_HEIGHT; y++){
                for(size_t x = 0; x < VGA_WIDTH; x++){
                    terminal_buffer[y*VGA_WIDTH + x] = terminal_buffer[(y+1)*VGA_WIDTH + x];
                }
            }
        }
    }
    
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++){
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

//uint32 to hex string
void itoh(uint32_t input, char* output){
    output[0] = 'x';
    for(int32_t i = 1; i < 9; i++){
        char in = (input >> (32-(i*4))) & 0xf;
        switch(in){
            case 10:{
                output[i] = 'A'; 
                break;
            }
            case 11:{
                output[i] = 'B'; 
                break;
            }
            case 12:{
                output[i] = 'C'; 
                break;
            }
            case 13:{
                output[i] = 'D'; 
                break;
            }
            case 14:{
                output[i] = 'E'; 
                break;
            }
            case 15:{
                output[i] = 'F'; 
                break;
            }
            default:{
                output[i] = in+48;
                break;
            }
        }
    }
    return;
}

void kernel_main(void)
{
    terminal_init();
    terminal_writestring("Lolis are a great example for this.\nSmall, but good\n");
    //terminal_buffer[1] = vga_entry('1', terminal_color);
    //terminal_buffer[1+VGA_WIDTH] = vga_entry('2', terminal_color);
    char tmp[15];
    itoh(0x123f, tmp);
    terminal_writestring(tmp);

    while (true){
        char kbStr[2];
        keyboard_to_string(kbStr);
        terminal_writestring(kbStr);
    }
    //terminal_writestring("\x30\n");
    //terminal_writestring("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n");
    terminal_writestring("lolis, nl:\nnext line");
}