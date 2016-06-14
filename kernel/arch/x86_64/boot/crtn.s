.section .init
	// GCC should place crtend.o init code here
	pop %rbp
	ret

.section .fini
	// GCC should place crtend.o fini code here
	pop %rbp
	ret
