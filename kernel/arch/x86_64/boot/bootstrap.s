// 32-bit code for now - we've not yet jumped into long mode
.code32

// Declare kernel constants
.set KERNEL_VMA, 0xC0000000

// Allocate a temporary 16 KB bootstrap stack
.section .bootstrap_stack, "aw", @nobits
	_stack_bottom:
	.skip 0x4000	// 16 KB
	_stack_top:

.section .data
	// Temporary GDT in order to jump to long mode
	.global _tmp_gdt
	.global _tmp_gdt_null
	.global _tmp_gdt_code0
	.global _tmp_gdt_data0
	.global _tmp_gdt_code3
	.global _tmp_gdt_data3
	.global _tmp_gdt_tss
	.global _tmp_gdt_end

	.align 8 //The GDT should be aligned to 64-bits (8 bytes)
	_tmp_gdt:

		// Basically, the GDT defines segments that the computer is permitted to
		// access. Since segment are deprecated in long (64-bit) mode, we just tell
		// the CPU to create two segments (one for code, one for data) that span the
		// ENTIRE address space. For future reference, each segment is 8 bytes in
		// size

		// We also define a null segment. It has to be there to conform to GDT
		// operation. We just set it to 0.

	_tmp_gdt_null:
		.long 0
		.long 0
	_tmp_gdt_code0: // For kernel-space code
		.word 0			// Limit [ 0:15]
		.word 0			// Base  [ 0:15]
		.byte 0			// Base  [16:23]
		.byte 0x98		// Present, Descriptor Privilege Level = 0, Execute/Read, non-conforming
		.byte 0xA0		// Granularity, 32-bit, limit [16:19]
		.byte 0			// Base  [24:31]
	_tmp_gdt_data0: // For kernel-space data
		.word 0			// Limit [ 0:15]
		.word 0			// Base  [ 0:15]
		.byte 0			// Base  [16:23]
		.byte 0x92		// Present, Descriptor Privilege Level = 0, Read/Write
		.byte 0xCF		// limit [16:19] and attr
		.byte 0			// Base  [24:31]
	_tmp_gdt_code3: // For user-space code
		.word 0			// Limit [ 0:15]
		.word 0			// Base  [ 0:15]
		.byte 0			// Base  [16:23]
		.byte 0xF8		// Present, Descriptor Privilege Level = 3, Execute/Read, non-conforming
		.byte 0xA0		// Granularity, 32-bit, limit [16:19]
		.byte 0			// Base  [24:31]
	_tmp_gdt_data3: // For user-space data
		.word 0			// Limit [ 0:15]
		.word 0			// Base  [ 0:15]
		.byte 0			// Base  [16:23]
		.byte 0xF2		// Present, Descriptor Privilege Level = 3, Read/Write
		.byte 0xCF		// limit [16:19] and attr
		.byte 0			// Base  [24:31]
	_tmp_gdt_end:

// Next, we define a pointer to the GDT. This is important because it informs
// the CPU of the upper and lower bounds of the GDT (limit and base
// respectively). Notice how this is (word + double) in size (10 bytes). This is
// the value that will eventually be placed into the GDTR register to tell the
// CPU where the GDT is

_tmp_gdt_pointer:
	.word (. - _tmp_gdt_end - 1)	// Limit: Here we just grab the GDT's end label and subtract 1 (the limit defines the last byte of the GDT)
	.long _tmp_gdt				// Base: This one is obvious. It's just a pointer to the GDT

// How paging works:
//
//    PML4             PDP              PD           Physical Mem
//  ________         ________         ________         ________
// |________|       |________|       |________|       |________|
// |________| ----> |________|       |________|       |________|
// |________|       |________|       |________| ----> |________|
// |________|       |________| ----> |________|       |________|
// |________|       |________|       |________|       |________|
// |________|       |________|       |________|       |________|
//
// Since we're using 2MB pages...
// ...We're creating 1 PML4 entry
// ...We're creating 1x4 PDP entries
// ...We're creating 1x4x512 PD entries
// ...And so we're mapping 1x4x512x2MB = 4GB of physical memory

.section .bss
	.align 0x1000		// Align to 4KB (4096 bytes)

	.global _page_map_level_4_top
	_page_map_level_4_top:		// A label to tell us where the top is
		.skip 0x6000			// Here we reserve enough bytes to store 24 KB worth of page tables
	.global _page_map_level_4_bottom
	_page_map_level_4_bottom:	// A label to tell us where the bottom is

// Some initial code
.section .text
.code32
	.global _start
	.type _start, @function
	_start:
		// 32-bit bootstrap. Here, we jump into long mode
		// First, disable interrupts
		cli

		// Set the stack pointer to the top of the temporary stack
		movl $(_stack_top), %esp

		// Clear EBP and EFLAGS
		mov $0, %ebp
		pushl 0
		popl %eax

		// Jump to the _enter_long procedure
		jmp _enter_long

	// Set the size of the _start label to the current location minus its beginning position
	.size _start, . - _start

	// Define a global label '_halt32'
	.global _halt32
	_halt32:
		cli			// Turn off CPU interrupts
		hlt			// Halt the CPU
		jmp _hang32	// Should the CPU become un-halted, hang it instead

	// Define a global label '_hang32'
	.global _hang32
	_hang32:
		jmp _hang32	// Infinite loop

	_enter_long:
		// Disable paging
		mov %cr0, %eax			// Move the cr0 (control) register into the accumulator
		and $(0x7FFFFFFF), %eax	// Set the PG (paging) bit (bit 31, FYI) to 0 in the accumulator
		mov %eax, %cr0			// Move the new accumulator value back into cr0

		// Set the PAE (Physical Address Extension) paging bit in cr4. This means we're enabling long addresses!
		mov %cr4, %eax			// Temporarily place the cr4 register into the accumulator
		bts $5, %eax			// Enable the PAE bit in the accumulator
		mov %eax, %cr4			// Place the new accumulator value back into the cr4 register

		// Set the IA32_EFER.LME (Long-Mode Enable) bit. 'EFER' Is the Extended
		// Feature Register. Another step towards fully entering long-mode
		mov $0xc0000080, %ecx	// Place the MSR address into the counter register
		rdmsr					// Load the contents of the 64-bit MSR into registers EDX:EAX. This is done because EDX & EAX are both 32-bit
		or $(1 << 8), %eax		// Set the 40th bit (the LME bit) (we use the 8th bit of EAX because the MSR is in EDX:EAX, which are both 32-bit)
		wrmsr					// Return the contents of registers EDX:EAX back into the 64-bit MSR

		// Construct the page tables. This is used for the shiny new long (64-bit)
		// mode paging system. We've already specified where this space is allocated
		jmp _construct_page_tables			// Now that the CR3 knows where the page tables are, we can construct them

	_kernel_panic_write_error:
		mov (%ebx), %dx
		mov %dx, (%eax)
		add $1, %eax
		movb $((4 << 4) | (15 << 0)), (%eax)
		add $1, %eax
		add $1, %ebx
		sub $1, %ecx
		jnz _kernel_panic_write_error

		/*mov $(0xB8000 + 0x00), %eax
		movw $('K' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x02), %eax
		movw $('e' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x04), %eax
		movw $('r' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x06), %eax
		movw $('n' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x08), %eax
		movw $('e' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x0A), %eax
		movw $('l' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x0C), %eax
		movw $(' ' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x0E), %eax
		movw $('P' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x10), %eax
		movw $('a' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x12), %eax
		movw $('n' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x14), %eax
		movw $('i' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x16), %eax
		movw $('c' | (4 << 12) | (15 << 8)), (%eax)
		mov $(0xB8000 + 0x18), %eax
		movw $('!' | (4 << 12) | (15 << 8)), (%eax)*/

		cli
		hlt

	//Since we're jumping into a procedure (see line above) we need to have a label back into this one afterwards
	_enter_compatibility_page_table_return:

		// Re-enable paging ready for the JUMP TO LONG-MODE, CHEWIE!
		mov %cr0, %eax			// Temporarily place the 0th control register into the accumulator
		or $(1 << 31), %eax		// Enable the 31st bit (the paging bit) in the accumulator (set it to 1)
		mov %eax, %cr0			// Move the modified control-register value back into cr0 from the accumulator

		// Here's where we actually set the GDT. We don't set the GDT register manually, but
		// we have an instruction that does it for us (lgdt)
		lgdt _tmp_gdt_pointer

		// CHEWIE! HIT THE LONG-MODE DRIVE!
		pushl $0x8				// We're not actually using a proper far-jump here. We just define a segment base (pretty sure it can be anything)...
		mov KERNEL_VMA, %eax
		add $_start64, %eax
		pushl %eax				// ...and then we push the location we want to jump to as well
		lret					//Then (bit of a hack) we simulate a far return with the data we just pushed

	_construct_page_tables:		// A label so we can access this procedure from elsewhere

		// First, we should set about clearing the 24KB of page table space. This
		// *should* be already done, but since we can't guarantee this, we're going
		// to clear it anyway.

		/* CLEAR PAGING TABLES */

		mov $(_page_map_level_4_top), %edi	// Put the PML4 pointer temporarily into a general-purpose register
		mov %edi, %cr3						// Tell CR3 where the page tables are located
		xor %eax, %eax						// Zero the accumulator just in case it wasn't already zero
		mov $0x6000, %ecx					// Move 0x6000 (24KB) into the counter register
		rep									// Repeatedly copy the value in the accumulator (0) into memory, as per the number of times in the counter (6KB)
		//stosd								// Copy EAX to EDI (Why? Not sure)
		mov %cr3, %edi						// Copy CR3 into EDI

		/* FILL PML4 */

		// Create a PML4 entry (PML4E)
		movl $0x1007, (%edi)				// Read/write and user-space permissions (note: 0x7 = 0b111) and 4KB offset. Presumably because this memory is aligned with 4KB anyway, any smaller value here is treated as data about permissions. Yes, it's confusing
		addl $(_page_map_level_4_top), (%edi)	// Points to PML4 + 4KB (specified on line above ^)

		add $0x1000, %edi					// Now increment EDI to PML4 location + 4KB (The PDP Table)

		/* FILL PDP */

		// Now we're creating 4 Page Directory Pointer Entries (PDPE)
		movl $0x2007, (%edi)		// Present, read/write permissions, user-space
		addl $(_page_map_level_4_top), (%edi)	// Points to PML4 + 8KB
		add $8, %edi //Increment to the next PDPE (we're making a table after all...)

		movl $0x3007, (%edi)		// Present, read/write permissions, user-space
		addl $(_page_map_level_4_top), (%edi)	// Points to PML4 + 12KB
		add $8, %edi //Increment to the next PDPE

		movl $0x4007, (%edi)		// Present, read/write permissions, user-space
		addl $(_page_map_level_4_top), (%edi)	// Points to PML4 + 16KB
		add $8, %edi //Increment to the next PDPE

		movl $0x5007, (%edi)		// Present, read/write permissions, user-space
		addl $(_page_map_level_4_top), (%edi)	// Points to PML4 + 20KB
		// We don't need to increment this one... We're at the end of this PDP!

		add $(0x1000 - 24), %edi //Increment to the Page Directory (PD) (not PDPE, hence the bigger jump. We have to go backwards 24 bytes though, since we just incremented by that many (see the crap above))

		// Here we go! The last part of page table construction. This is the weird
		// part because we're looping. Keep all limbs within the vehicle, grab hold
		// of your hair and kiss your sanity goodbye

		/* FILL PD */

		// Create 4 * 512 Page Directory Entries (PDE)
		mov $0x00000087, %ebx		// Present, read/write, 2MB granularity (i.e: Each page is 2MB)
		mov $(4 * 512), %ecx		// We are making 4 * 512 entries after all...

	_set_pdp_entry:					// This is our little loop label
		movl %ebx, (%edi)			// Move EBX (i.e: the permissions we're currently talking about) into the correct location
		add $(1 << 21), %ebx		// Increment by 0x200000 (2MB). So basically skip to the next page location
		add $8, %edi				// Increment! We're done with this entry, go to the next one.
		loop _set_pdp_entry			// Loop until the counter is 0

		// Return back to the previous procedure
		jmp _enter_compatibility_page_table_return
