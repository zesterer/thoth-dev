#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/string.h"

#include "thoth/time.h"
#include "thoth/io.h"
#include "thoth/mem.h"
#include "thoth/vfs/vfs.h"

// New C++ headers
#include "thoth/kernel/driver/vga/vga.hpp"
#include "thoth/kernel/driver/serial/serial.hpp"
#include "thoth/kernel/driver/cmos/cmos.hpp"
#include "thoth/std/io.hpp"

#include "thoth/kernel/vns/vns.hpp"

#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
	#include "thoth/vga.h"
#endif

extern void* kernel_end asm("_kernel_end");

extern "C" void kernel_early()
{
	#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
		Thoth::Status status = Thoth::Kernel::Driver::VGA::Init();
	#endif

	thoth_io_check("Entered kernel bootstrap", STATUS_SUCCESS);

	#if defined(THOTH_ARCH_x86_64)
		thoth_io_check("Created temporary GDT", STATUS_SUCCESS);
		thoth_io_check("Jumped to 64-bit mode", STATUS_SUCCESS);
	#endif

	#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
		thoth_io_check("Initiating VGA terminal", status.getError());
	#endif

	thoth_io_check("Kernel bootstrap complete", STATUS_INFO);
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
	thoth_io_check("Entered kernel main", STATUS_SUCCESS);

	// Dynamic Memory Map
	int dmm_status = thoth_mem_init((void*)0x1000000, 0x100000, 256); // At 16 MB, 1 MB in size, composed of blocks of 256 B
	thoth_io_check("Initiating kernel dynamic memory", !(dmm_status == 0));

	Thoth::Status status_serial = Thoth::Kernel::Driver::Serial::Init();
	thoth_io_check("Initiating kernel serial driver", status_serial.getError());

	Thoth::Status status_cmos = Thoth::Kernel::Driver::CMOS::Init();
	thoth_io_check("Initiating kernel CMOS driver", status_cmos.getError());

	// Virtual File System
	//int vfs_status = thoth_vfs_init();
	Thoth::Status status_vfs = Thoth::Kernel::VNS::Init();
	thoth_io_check("Initiated kernel VFS", status_vfs.getError());
	unsigned long dir = (unsigned long)Thoth::Kernel::VNS::NodeAttribute::DEFAULT_DIR;
	Thoth::Kernel::VNS::Node* r0 = Thoth::Kernel::VNS::GetVNS().getValue()->getRoot().getValue();
	Thoth::Kernel::VNS::Node* n1 = r0->addChild("bin", dir).getValue();
	Thoth::Kernel::VNS::Node* n2 = n1->addChild("hello-world").getValue();
	Thoth::Kernel::VNS::Node* n3 = r0->addChild("dev", dir).getValue();
	Thoth::Kernel::VNS::Node* n4 = n3->addChild("serial", dir).getValue();
	Thoth::Kernel::VNS::Node* n5 = n3->addChild("COM1").getValue();
	Thoth::Kernel::VNS::Node* n6 = n3->addChild("COM2").getValue();
	Thoth::Kernel::VNS::Node* n7 = n1->addChild("extra", dir).getValue();
	Thoth::Kernel::VNS::Node* n8 = n7->addChild("test-exec").getValue();
	Thoth::Kernel::VNS::Node* n9 = n7->addChild("examples", dir).getValue();
	r0->getNode("/bin/extra/examples").getValue()->addChild("example0");
	Thoth::Kernel::VNS::DisplayMap();

	thoth_io_check("Boot sequence complete", STATUS_INFO);

	kernel_welcome();

	Thoth::Std::IO::PrintFormat("Opening '%s' serial port: baud=%i, databits=%i, bufbits=%i, parity=%s...\n", "COM2", 57600, 8, 1, "ODD");
	Thoth::Kernel::Driver::Serial::InitPort(Thoth::Kernel::Driver::Serial::Port::COM1, 57600, 8, 1, Thoth::Kernel::Driver::Serial::Parity::ODD);
	Thoth::Std::IO::PrintFormat("Outputting string '%s' to serial...\n", "Hello, World! This is some serial output on the COM2 port at a baud rate of 57600 Hz, 8 databits, 1 buffer bit and odd transmission parity!");
	Thoth::Kernel::Driver::Serial::WriteStr(Thoth::Kernel::Driver::Serial::Port::COM1, "Hello, World! This is some serial output on the COM2 port at a baud rate of 57600 Hz, 8 databits, 1 buffer bit and odd transmission parity!\n");

	/*Thoth::Std::IO::PrintFormat("Hello, there! Here's the number twelve:%iand four hundred and six as hex:%X\n", 12, 406);

	THOTH_VFS_NODE_ID root = thoth_vfs_get_root();
	THOTH_VFS_NODE_ID testdir = thoth_vfs_create_node("testdir", root, THOTH_VFS_DIRECTORY);
	THOTH_VFS_NODE_ID file1 = thoth_vfs_create_node("file1", testdir, THOTH_VFS_FILE);
	THOTH_VFS_NODE_ID file2 = thoth_vfs_create_node("file2", root, THOTH_VFS_FILE);
	//thoth_vfs_delete_node(testdir);
	thoth_vfs_display();*/

	// Dynamic memory test
	/*{
		thoth_mem_display(32);
		void* a = malloc(3);
		thoth_mem_display(32);
		void* b = malloc(4000);
		thoth_mem_display(32);
		void* c = malloc(3);
		thoth_mem_display(32);
		void* d = malloc(2100);
		thoth_mem_display(32);

		free(a);
		thoth_mem_display(32);
		free(b);
		thoth_mem_display(32);
		free(c);
		thoth_mem_display(32);
		free(d);
		thoth_mem_display(32);

		char* msg = malloc(1024);
		strcpy("Hello, World! This is a memory-managed string!\n", msg);
		thoth_mem_display(32);
		printf(msg);
	}*/

	// CPU cycle clock
	while (false)
	{
		if (rdtsc_n() % 10000000 == 0)
		{
			printf("Tick!\n");
			break;
		}
	}

	Thoth::Kernel::Driver::CMOS::Update();
	//for (int i = 0; i < 256; i ++)
	//	Thoth::Std::IO::PrintFormat("%i,", Thoth::Kernel::Driver::CMOS::GetRegister(i));
}
