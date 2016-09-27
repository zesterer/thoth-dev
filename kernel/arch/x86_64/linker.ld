/* Entry point of the operating system. The bootloader will begin execution at this label */
ENTRY(_start)

/* What is the binary output format? */
OUTPUT_FORMAT(elf64-x86-64)

SECTIONS
{
	/* KERNEL_VMA = 0xC0000000; */
	KERNEL_VMA = 0x00000000;

	/* Offset the kernel at 1MB (to avoid interfering with the bootloader or any low-level initial code */
	. = 1M;

	.bootstrap BLOCK(4K) : ALIGN(4K)
	{
		/* Place the MultiBoot header at a convenient location for the bootloader to find */
		*(.multiboot)
		arch/x86_64/boot/bootstrap.o(.text)
	}

	. += KERNEL_VMA;

	/* Place executable code within its own 4KB-aligned block */
	.text BLOCK(4K) : AT(ADDR(.text) - KERNEL_VMA)
	{
		_code = .;
		/* Place actual kernel code after the MultiBoot header so the bootloader knows where to find it */
		*(EXCLUDE_FILE(*arch/x86_64/boot/bootstrap.o) .text)
	}

	/* Read-only data */
	.rodata BLOCK(4K) : AT(ADDR(.rodata) - KERNEL_VMA)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : AT(ADDR(.data) - KERNEL_VMA)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and initial kernel stack */
	.bss BLOCK(4K) : AT(ADDR(.bss) - KERNEL_VMA)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}

	.kernel_end BLOCK(4K) : AT(ADDR(.kernel_end) - KERNEL_VMA)
	{
		*(.kernel_end)
	}

	/* Any other sections produced by the compiler *should* be placed after this point */
}
