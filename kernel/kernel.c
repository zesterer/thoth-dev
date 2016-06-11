#include "cstd/str.h"
#include "cstd/mem.h"
#include "cstd/io.h"
#include "cstd/conv.h"

extern void* kernel_end asm("_kernel_end");

enum status_mode { STATUS_SUCCESS = 0, STATUS_INFO = 2, STATUS_FAIL = 1, };

void terminal_write_check(const char* msg, int status)
{
	if (status == STATUS_SUCCESS)
		cstd_io_print("[  $F2OK$FF  ] ");
	else if (status == STATUS_FAIL)
		cstd_io_print("[ $F4FAIL$FF ] ");
	else if (status == STATUS_INFO)
		cstd_io_print("[ $F3INFO$FF ] ");

	cstd_io_print(msg);
	cstd_io_put('\n');
}

void kernel_early()
{
	cstd_io_init();

	terminal_write_check("Entered kernel bootstrap", STATUS_SUCCESS);
	terminal_write_check("Initialized VGA terminal", STATUS_SUCCESS);
}

void kernel_main()
{
	int result = cstd_mem_init((void*)0x400000, 0x100000, 1024); // At 4 MB, 1 MB in size, composed of blocks of 1 KB
	terminal_write_check("Initiated kernel dynamic memory", !(result == 0));

	terminal_write_check("Boot sequence complete", STATUS_INFO);

	cstd_io_print("\n$B8Welcome to Thoth$B0\n");

	cstd_mem_display(32);
	void* a = cstd_mem_allocate(3);
	cstd_mem_display(32);
	void* b = cstd_mem_allocate(4000);
	cstd_mem_display(32);
	void* c = cstd_mem_allocate(3);
	cstd_mem_display(32);
	void* d = cstd_mem_allocate(2100);
	cstd_mem_display(32);

	cstd_mem_free(a);
	cstd_mem_display(32);
	cstd_mem_free(b);
	cstd_mem_display(32);
	cstd_mem_free(c);
	cstd_mem_display(32);
	cstd_mem_free(d);
	cstd_mem_display(32);

	char* msg = cstd_mem_allocate(1024);
	cstd_str_copy("Hello, this is a memory-managed string!\n", msg);
	cstd_mem_display(16);
	cstd_io_print(msg);
}
