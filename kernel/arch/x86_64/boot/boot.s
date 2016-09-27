// Long (64-bit) mode code from now on!
.code64

	// The long (64-bit) mode bootstrap
	.global _start64
	_start64:

		// We now have a C-worthy (get it?) environment
		// Time to jump into kernel early C
		call kernel_early

		// Call C constructor code and others
		call _init

		// Main kernel code
		call kernel_main

		// If the kernel call returns, halt the system
		jmp _halt64

	// Define a global label '_halt64'
	.global _halt64
	_halt64:
		cli			// Turn off CPU interrupts
		hlt			// Halt the CPU
		jmp _hang64	// Should the CPU become un-halted, hang it instead

	// Define a global label '_hang64'
	.global _hang64
	_hang64:
		jmp _hang64	// Infinite loop

// Set the size of the _start label to the current location minus its beginning position
.size _start64, . - _start64

// So we know where the end of the kernel is
.section .kernel_end
	.global _kernel_end
	_kernel_end:
