#ifndef THOTH_KERNEL_THOTH_IO
#define THOTH_KERNEL_THOTH_IO

#include "stdint.h"

enum status_mode
{
	STATUS_SUCCESS = 0,
	STATUS_INFO = 2,
	STATUS_FAIL = 1,
};

void thoth_io_outb(uint16_t port, uint8_t val);
uint8_t thoth_io_inb(uint16_t port);

void thoth_io_check(const char* msg, int status);

#endif
