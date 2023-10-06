#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <kernel/tty.h>
 
#include "vga.h"
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) 
	{
		for (size_t x = 0; x < VGA_WIDTH; x++) 
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_scroll() // puts each line above by 1
{
	for(size_t y = 1; y < VGA_HEIGHT; y++) // y = 1 because the first row will be shifted out of the screen
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			size_t index = y * VGA_WIDTH + x;
			size_t new_index = index - VGA_WIDTH;
				
			terminal_buffer[new_index] = terminal_buffer[index]; // character at pos VGA_WIDTH + 2 needs to be shifted to pos 2
		} // this will shift all rows up by 1
	}
}
 
void terminal_delete_last_line() 
{
	int* ptr;
 
	for(size_t x = 0; x < VGA_WIDTH * 2; x++) 
	{
		ptr = 0xB8000 + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x;
		*ptr = 0;
	}
}
 
void terminal_putchar(char c) 
{	
	if(c != '\n')
	{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		terminal_column++;
	}
	
	else
	{
		terminal_column = 0;
		terminal_row++;
	}
	
	if(terminal_column == VGA_WIDTH)
	{
		terminal_column = 0;
		terminal_row++;
	}
	
	if(terminal_row == VGA_HEIGHT)
	{
		terminal_scroll();		
		terminal_delete_last_line();
		terminal_row = VGA_HEIGHT - 1;
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}
