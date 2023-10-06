#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void) 
{
#if defined(__is_libk)
	// todo: add proper kernel panic
	printf("kernel: panic: abort()\n");
#else
	// todo: abnormally terminate the process as if by SIGABRT
	printf("abort()\n");
#endif
	while (1) { }
	__builtin_unreachable();
}
