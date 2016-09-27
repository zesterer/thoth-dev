// Declare multiboot constants
.set ALIGN,	1 << 0
.set MEMINFO,	1 << 1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

// Multiboot header
.section .multiboot
	.global _multiboot_header
	_multiboot_header:
		.align 4
		.long MAGIC
		.long FLAGS
		.long CHECKSUM

		.long _multiboot_header
		.long 0						// Will eventually be kernel_text_start when kernel is loaded
		.long 0						// Will eventually be kernel_data_end when kernel is loaded
		.long 0						// Will eventually be kernel_bss_end when kernel is loaded
