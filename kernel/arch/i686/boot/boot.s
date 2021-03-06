// Declare multiboot constants
.set ALIGN,	1 << 0
.set MEMINFO,	1 << 1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

// Allocate the multiboot header
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

// Allocate a temporary 16 KB bootstrap stack
.section .bootstrap_stack, "aw", @nobits
	_stack_bottom:
	.skip 0x4000	// 16 KB
	_stack_top:

// Now for some actual code
.section .text
	// Define a global label '_start'
	.global _start
	.type _start, @function
	_start:
		// Now we have kernel code
		// The first job is to tell the stack pointer where the bootstrap stack is
		movl $_stack_top, %esp

		// We now have a C-worthy (get it?) environment
		// Time to jump into kernel early C
		call kernel_early

		// Call C constructor code and others
		call _init

		// Main kernel code
		call kernel_main

		// If the kernel call returns, halt the system
		jmp _halt

	// Define a global label '_halt'
	.global _halt
	_halt:
		cli		// Turn off CPU interrupts
		hlt		// Halt the CPU
		jmp _hang	// Should the CPU become un-halted, hang it instead

	// Define a global label '_hang'
	.global _hang
	_hang:
		jmp _hang	// Infinite loop

// Set the size of the _start label to the current location minus its beginning position
.size _start, . - _start

// So we know where the end of the kernel is
.section .kernel_end
	.global _kernel_end
	_kernel_end:
