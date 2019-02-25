#include <stdio.h>
#include <OS.h>

#ifdef __cplusplus
extern "C" {
#endif

//#define WRAPPREFIX wrapped_
#define WRAPPREFIX __real_
//#define UNWRAPPREFIX __real_
/*
status_t convert_from_utf8__FUlPCcPlPcT2T2c(unsigned long a, char const *b, long *c, char *d, long *e, long *f, char g);
status_t convert_to_utf8__FUlPCcPlPcT2T2c(unsigned long a, char const *b, long *c, char *d, long *e, long *f, char g);
*/
/*
00000e14 T convert_from_utf8__FUlPCcPlPcT2T2c
00000e14 T convert_from_utf8(unsigned long, char const *, long *, char *, long *, long *, char)
00000a80 T convert_to_utf8__FUlPCcPlPcT2T2c
00000a80 T convert_to_utf8(unsigned long, char const *, long *, char *, long *, long *, char)
*/

status_t __wrap_convert_from_utf8__FUlPCcPlPcT2T2c(unsigned long a, char const *b, long *c, char *d, long *e, long *f, char g)
{
	return __real_convert_from_utf8__FUlPCcPlPcT2T2c(a, b, c, d, e, f, g);
}

/*
status_t convert_from_utf8__FUlPCcPlPcT2T2c(unsigned long a, char const *b, long *c, char *d, long *e, long *f, char g) 
			__attribute__ ((weak, alias ("wrapped_convert_from_utf8__FUlPCcPlPcT2T2c")));
*/
status_t __wrap_convert_to_utf8__FUlPCcPlPcT2T2c(unsigned long a, char const *b, long *c, char *d, long *e, long *f, char g)
{
	return __real_convert_to_utf8__FUlPCcPlPcT2T2c(a, b, c, d, e, f, g);
}
/*
status_t convert_to_utf8__FUlPCcPlPcT2T2c(unsigned long a, char const *b, long *c, char *d, long *e, long *f, char g)
			__attribute__ ((weak, alias ("wrapped_convert_to_utf8__FUlPCcPlPcT2T2c")));
*/





#ifdef __cplusplus
}
#endif

