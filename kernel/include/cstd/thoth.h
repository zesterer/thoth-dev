#ifndef THOTH_KERNEL_CSTD_THOTH
#define THOTH_KERNEL_CSTD_THOTH

enum status_mode
{
	STATUS_SUCCESS = 0,
	STATUS_INFO = 2,
	STATUS_FAIL = 1,
};

void putscheck(const char* msg, int status);

#endif
