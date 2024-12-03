
#include <stdio.h>
#include <stdarg.h>
#include "debug.h"

__attribute__((target("arm")))
void print_vba(const char *str, ...)
{
	char buf[128];
	va_list arg_list;

	va_start(arg_list, str);
	vsnprintf(buf, 128, str, arg_list);
	va_end(arg_list);

	__asm__ __volatile__(
		"mov r0, %0\n\t"
		"swi 0xff0000\n\t" :
		: "r" (buf)
		: "r0"
	);
}
