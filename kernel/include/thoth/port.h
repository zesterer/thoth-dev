#ifndef THOTH_KERNEL_THOTH_PORT
#define THOTH_KERNEL_THOTH_PORT

#include "stdint.h"

void	thoth_port_outb(uint16_t port, uint8_t val);
uint8_t	thoth_port_inb(uint16_t port);

#endif
