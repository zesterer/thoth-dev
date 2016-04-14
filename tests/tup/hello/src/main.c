#include "stdio.h"

#include "hello/output.h"
#include "square/square.h"

int main(int argc, char* argv[])
{
	output("Hello, World!");

	printf("square(4) = %i\n", square(4));
	
	return 0;
}
