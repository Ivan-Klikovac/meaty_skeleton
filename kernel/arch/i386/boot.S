# multiboot header constants
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets the bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above to prove multiboot

# multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# reserve a stack
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KB
stack_top:

# kernel entry point
.section .text
.global _start
.type _start, @function

_start:
	movl $stack_top, %esp

	# call the global constructors
	call _init

	# transfer control to kernel entry point
	call kernel_main

	# hang if kernel unexpectedly returns
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
