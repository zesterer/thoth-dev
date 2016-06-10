/* Entry point of the operating system. The bootloader will begin execution at this label */
ENTRY(_start)

SECTIONS
{
	/* Offset the kernel at 1MB (to avoid interfering with the bootloader or any low-level initial code */
	. = 1M;
	
	/* Place executable code within its own 4KB-aligned block */
	.text BLOCK(4K) : ALIGN(4K)
	{
		/* Place the MultiBoot header at a convenient location for the bootloader to find */
		*(.multiboot)
		/* Place actual kernel code after the MultiBoot header so the bootloader knows where to find it */
		*(.text)
	}
	
	/* Read-only data */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	
	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	
	/* Read-write data (uninitialized) and initial kernel stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	
	/* Any other sections produced by the compiler *should* be placed after this point */
}
