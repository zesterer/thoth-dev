#include "cstd/str.h"
#include "cstd/mem.h"
#include "cstd/io.h"

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

void kernel_main()
{
	cstd_io_init();

	terminal_write_check("Initiated kernel bootstrap", 0);
	terminal_write_check("Initialized VGA terminal", 0);

	int result = cstd_mem_init((void*)0x400000, 0x100000, 1024); // At 4 MB, 1 MB in size, composed of blocks of 1 KB
	terminal_write_check("Initiated kernel dynamic memory", !(result == 0));
	terminal_write_check("Boot sequence complete", 2);

	cstd_io_print("\n$B8Welcome to Thoth$B0");
}
