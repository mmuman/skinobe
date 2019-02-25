#include <stdio.h>
#include <OS.h>
#include <image.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

status_t (*convert_from_utf8_ptr)(unsigned long, char const *, long *, char *, long *, long *, char );
status_t (*convert_to_utf8_ptr)(unsigned long, char const *, long *, char *, long *, long *, char );

/*
status_t convert_from_utf8__FUlPCcPlPcT2T2c(unsigned long a, char const *b, long *c, char *d, long *e, long *f, char g);
status_t convert_to_utf8__FUlPCcPlPcT2T2c(unsigned long a, char const *b, long *c, char *d, long *e, long *f, char g);
*/

void _init_conv_utf8_ptrs(void)
{
	image_info ii;
	int32 cookie = 0;
/*
__asm__ ("
	jmp	(0x80000000+4)
");
*/
	while (get_next_image_info(0, &cookie, &ii) == B_OK) {
//		puts (ii.name);
		if (strncmp(ii.name + strlen(ii.name) - 18, "lib_te_gui_hack.so", 18) &&
			(get_image_symbol(ii.id, "convert_from_utf8__FUlPCcPlPcT2T2c", B_SYMBOL_TYPE_ANY, (void **)&convert_from_utf8_ptr) == B_OK) && 
			(get_image_symbol(ii.id, "convert_to_utf8__FUlPCcPlPcT2T2c", B_SYMBOL_TYPE_ANY, (void **)&convert_to_utf8_ptr) == B_OK) &&
			convert_from_utf8_ptr != NULL && convert_to_utf8_ptr != NULL)
			return;
//		puts("next");
	}
	
}

/*
00000e14 T convert_from_utf8__FUlPCcPlPcT2T2c
00000e14 T convert_from_utf8(unsigned long, char const *, long *, char *, long *, long *, char)
00000a80 T convert_to_utf8__FUlPCcPlPcT2T2c
00000a80 T convert_to_utf8(unsigned long, char const *, long *, char *, long *, long *, char)
*/

status_t convert_from_utf8__FUlPCcPlPcT2T2c(unsigned long a, char const *b, long *c, char *d, long *e, long *f, char g)
{
	return convert_from_utf8_ptr(a, b, c, d, e, f, g);
}
//			__attribute__ ((weak, alias ("wrapped_convert_from_utf8__FUlPCcPlPcT2T2c")));

status_t convert_to_utf8__FUlPCcPlPcT2T2c(unsigned long a, char const *b, long *c, char *d, long *e, long *f, char g)
{
	return convert_to_utf8_ptr(a, b, c, d, e, f, g);
}
//			__attribute__ ((weak, alias ("wrapped_convert_to_utf8__FUlPCcPlPcT2T2c")));





#ifdef __cplusplus
}
#endif

