#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/string.h"

#include "thoth/time.h"
#include "thoth/io.h"
#include "thoth/mem.h"

// New C++ headers
#include "thoth/kernel/driver/manager.hpp"
#include "thoth/kernel/driver/vns/vns.hpp"
#include "thoth/kernel/driver/vga/vga.hpp"
#include "thoth/kernel/driver/serial/serial.hpp"
#include "thoth/kernel/driver/cmos/cmos.hpp"
#include "thoth/std/io.hpp"

#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
	#include "thoth/vga.h"
#endif

extern void* kernel_end asm("_kernel_end");

extern "C" void kernel_early()
{
	#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
		Thoth::Status status = Thoth::Kernel::Driver::VGA::Init();
		thoth_io_check("Initiating VGA terminal", status.getError());
	#endif

	// Dynamic Memory Map
	int dmm_status = thoth_mem_init((void*)0x1000000, 0x100000, 256); // At 16 MB, 1 MB in size, composed of blocks of 256 B
	thoth_io_check("Initiating dynamic memory pool", !(dmm_status == 0));

	thoth_io_check("Finished kernel boostrap", STATUS_INFO);
}

void kernel_welcome()
{
	// Print welcome message
	printf("\n$B8Welcome to Thoth $B0\n");

	// Print version
	printf("$B8Version:$B0$F3 ");
	printf(THOTH_VERSION);
	printf("$FF\n");

	// Print arch
	printf("$B8Arch   :$B0$F3 ");
	printf(THOTH_ARCH);
	printf("$FF\n");
}

static inline uint64_t rdtsc_n()
{
    uint64_t ret;
    asm volatile ( "rdtsc" : "=A"(ret) );
    return ret;
}

extern "C" void kernel_main()
{
	Thoth::Kernel::Driver::Manager manager;

	thoth_io_check("Entered kernel", STATUS_INFO);

	// Initiate Driver Manager
	manager.init();

	manager.addHook(Thoth::Kernel::Driver::VNS::GenDriver().getValue());
	manager.addHook(Thoth::Kernel::Driver::Serial::GenDriver().getValue());
	manager.addHook(Thoth::Kernel::Driver::CMOS::GenDriver().getValue());

	// Initiate all drivers
	manager.initAll();

	thoth_io_check("Boot process complete", STATUS_INFO);

	kernel_welcome();

	/*
	Thoth::Std::IO::PrintFormat("Opening '%s' serial port: baud=%i, databits=%i, bufbits=%i, parity=%s...\n", "COM2", 57600, 8, 1, "ODD");
	Thoth::Kernel::Driver::Serial::InitPort(Thoth::Kernel::Driver::Serial::Port::COM1, 57600, 8, 1, Thoth::Kernel::Driver::Serial::Parity::ODD);
	Thoth::Std::IO::PrintFormat("Outputting string '%s' to serial...\n", "Hello, World! This is some serial output on the COM2 port at a baud rate of 57600 Hz, 8 databits, 1 buffer bit and odd transmission parity!");
	Thoth::Kernel::Driver::Serial::WriteStr(Thoth::Kernel::Driver::Serial::Port::COM1, "Hello, World! This is some serial output on the COM2 port at a baud rate of 57600 Hz, 8 databits, 1 buffer bit and odd transmission parity!\n");
	*/

	// CPU cycle clock
	while (false)
	{
		if (rdtsc_n() % 10000000 == 0)
		{
			printf("Tick!\n");
			break;
		}
	}
}
