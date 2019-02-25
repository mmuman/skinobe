#include <stdio.h>
#include <unistd.h>
#include <OS.h>
#include <InterfaceDefs.h>

#ifndef B_BEOS_VERSION_DANO
extern struct ui_info {
	rgb_color a, b, c, d;
} *_ui_info_ptr_;
#endif

#ifdef __cplusplus
extern "C" {
#endif

void _init_hacked_colors(void)
{
#ifndef B_BEOS_VERSION_DANO
#if 0
	int i;
	puts("libhack:init_hacked_colors()");
	_ui_info_ptr_->d.red = 255;
	_ui_info_ptr_->d.green = 0;
	_ui_info_ptr_->d.blue = 0;

	printf("libhack: _ui_info_ptr_ = 0x%08lx\n", _ui_info_ptr_);
/*
	i = open("/boot/home/uicolslog.txt", O_WRONLY | O_CREAT, 0644);
	write(i, _ui_info_ptr_, 1024);
	close(i);
*/
#endif
#endif
}

#ifdef __cplusplus
}
#endif

