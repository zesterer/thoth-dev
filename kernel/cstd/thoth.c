#include "cstd/thoth.h"
#include "cstd/io.h"

void putscheck(const char* msg, int status)
{
	if (status == STATUS_SUCCESS)
		cstd_io_print("[  $F2OK$FF  ] ");
	else if (status == STATUS_FAIL)
		cstd_io_print("[ $FCFAIL$FF ] ");
	else if (status == STATUS_INFO)
		cstd_io_print("[ $F3INFO$FF ] ");
	else if (status == STATUS_INFO)
		cstd_io_print("[$F4ERROR!$FF] ");

	cstd_io_print(msg);
	cstd_io_put('\n');
}
