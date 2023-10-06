#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) 
{
	// priority todo:
	// gdt
	// idt

	// terminal stuff
	terminal_initialize();
	printf("test\n");
}
