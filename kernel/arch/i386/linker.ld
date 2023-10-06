// the bootloader will look at this image and start execution at the symbol designated as the entry point
ENTRY(_start)

// tell where the various sections of the object files will be put in the final kernel image
SECTIONS
{
	// begin putting sections at 1 MB, a conventional place for kernels to be loaded from by the bootloader
	. = 1M;

	// first put the multiboot header, as it is required to be put very early in the image or the bootloader won't recognize the format
	// next we'll put the .text section
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	// read-only data
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	// read-write data (initialized)
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	// Read-write data (uninitialized) and stack
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

	// the compiler may produce other sections, they need to be put here in order to be included in the final image
}
