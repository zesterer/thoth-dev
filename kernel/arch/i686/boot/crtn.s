.section .init
	// GCC should place crtend.o init code here
	popl %ebp
	ret

.section .fini
	// GCC should place crtend.o fini code here
	popl %ebp
	ret
