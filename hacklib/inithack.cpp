#include <stdio.h>
#include <OS.h>
//#include <UTF8.h>
#include <Alert.h>
//#include <SupportDefs.h>
#define _ZETA_TS_FIND_DIR_ // what a crappy fix
#include <FindDirectory.h>
#include <strings.h>
#include <unistd.h>

extern class BApplication *be_app;

#ifdef __cplusplus
extern "C" {
#endif

int32 BApp_created = 0;
int quit_requested_now = 0;
thread_id wait_for_bapp_tid = 0;

extern void _init_conv_utf8_ptrs(void);
extern void _init_libbe_trampolines(void);
extern void _init_hacked_colors(void);
extern void _init_app_msg_filter(void);
//extern status_t switch_gui_hooks(uint32 version, void **hooks);
extern status_t load_guiskin_plugin(const char *name);

//extern void *hooklist[];
/*
int32 wait_for_bapp(void *arg)
{
	bigtime_t waittime = 100;
	while (snooze(waittime) == B_OK) {
		if (quit_requested_now)
			return B_OK;
		if (be_app) {
			//snooze(100000);
//			(new BAlert("libbehack", "This is a test", "Ok"))->Go();
			BApp_created = 1;
			_init_app_msg_filter();
			return B_OK;
		}
		waittime += waittime;
		if (!waittime || waittime > 1000000)
			waittime = 100;
	}
	return B_OK;
}
*/

void _setup_gui_plugin_from_settings(void)
{
	int settings_fd;
	char pathbuf[B_PATH_NAME_LENGTH];
	find_directory(B_USER_SETTINGS_DIRECTORY, 0L, false, pathbuf, B_PATH_NAME_LENGTH);
	strcat(pathbuf, "/x-vnd.mmu_man.skinobe");
	fprintf(stderr, "user settings file: %s\n", pathbuf);
	settings_fd = open(pathbuf, O_RDONLY);
	if (settings_fd >= B_OK) {
		memset(pathbuf, 0, B_PATH_NAME_LENGTH);
		read(settings_fd, pathbuf, B_PATH_NAME_LENGTH - 1);
		close(settings_fd);
		load_guiskin_plugin(pathbuf);
	}
}

void initialize_after(void)
{
	//puts("libhack:initialize_after()");
	_init_conv_utf8_ptrs();
	_init_libbe_trampolines();
	_setup_gui_plugin_from_settings();
//	_init_hacked_colors();
//	wait_for_bapp_tid = spawn_thread(wait_for_bapp, "libbe hack wait4BApp", B_NORMAL_PRIORITY, NULL);
//	resume_thread(wait_for_bapp_tid);
	
}


void terminate_before(void)
{
//	status_t err;
//	quit_requested_now = 1;
	//puts("libhack:terminate_before()");
//	wait_for_thread(wait_for_bapp_tid, &err);
}





#ifdef __cplusplus
}
#endif

