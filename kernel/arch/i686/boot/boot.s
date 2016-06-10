// Declare multiboot constants
.set ALIGN,	1 << 0
.set MEMINFO,	1 << 1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

// Allocate the multiboot header
.section .multiboot
	.align 4
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

// Allocate a temporary 16 KB bootstrap stack
.section .bootstrap_stack, "aw", @nobits
	stack_bottom:
	.skip 0x4000	// 16 KB
	stack_top:

// Now for some actual code
.section .text
	// Define a global label '_start'
	.global _start
	.type _start, @function
	_start:
		// Now we have kernel code
		// The first job is to tell the stack pointer where the bootstrap stack is
		movl $stack_top, %esp
		
		// We now have a C-worthy (get it?) environment
		// Time to jump into kernel C
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
