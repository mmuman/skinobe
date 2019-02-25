#include <stdio.h>
#include <OS.h>
#include <image.h>
#include <strings.h>
#include <Application.h>
#include <Debug.h>
#include "config.h"
#include "gui_skin_plugin.h"

#ifdef WRAP_UI_COLOR
//#include <InterfaceDefs.h>
enum color_which{
B_NULL_COLOR
};
#endif

class BRect;

#ifdef DEBUG
//#undef DEBUG
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void _init_app_msg_filter(void);

extern void ReadyToRun__12BApplication(BApplication *_this);
extern thread_id Run__12BApplication(BApplication *_this);

extern int32 BApp_created;

image_id currentplugin = (image_id)0;

// The maximum amount of method prologue we can save, and search for the "call 0(ip)"
#define MAX_PROLOGUE 16

// The maximum number of supported hooks
#define MAX_HOOKS 16

// The maximum number of used hooks from the exported hooklist from plugins
#define NUMHOOKS 7

// The number of hooks not in public arrays (= offset)
#define PRIVATE_HOOK_COUNT 1

static unsigned char __static_saved_prologues[MAX_PROLOGUE * MAX_HOOKS] __attribute__ ((section (".text"))) =
{
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
 0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
};

typedef struct trampolist {
	void *orig;

		// hardcoded asm

	unsigned char nops[3];
	unsigned char jmp;
	void *hooked; // RELATIVE ! (not really a pointer =)

	unsigned char original_prologue[MAX_PROLOGUE];

	unsigned char nops2[3];
        unsigned char jmpback;
	void *backaddr; // RELATIVE ! (not really a pointer =)

} trampolist;

//                      { nop, nop, nop, }, nearjmp, hook, { nops }, { ret, nop, nop, nop, }, nearjmp, backaddr
#define EMPTY_JUMPFRAME { 0x90, 0x90, 0x90} , 0xe9, NULL, \
{ /*0xc3,*/0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }, \
{ 0x90, 0x90, 0x90} , 0xe9, NULL


#define TRAMPOLINE_1(a, b, c, d, args...) \
class d; \
extern c b (d *, ## args); \
//extern c hooked_##b (d *, ## args);

#define TRAMPOLINE_2(a, b, c, args...) \
extern c b (## args); \
//extern c hooked_##b (## args);

#define TRAMPOLINE_PRIV(a, b, c, d, args...)

#include "trampolist.h"

#undef TRAMPOLINE_1(a, b, c, d, args...)
#undef TRAMPOLINE_2(a, b, c, args...)
#undef TRAMPOLINE_PRIV(a, b, c, d, args...)

/*
#define TRAMPOLINE_1(a, b, c, d, args...) hooked_##b ,
#define TRAMPOLINE_2(a, b, c, args...) hooked_##b ,
#define TRAMPOLINE_PRIV(a, b, c, d, args...)
void *hooklist[] = {
#include "trampolist.h"
};
#undef TRAMPOLINE_1(a, b, c, d, args...)
#undef TRAMPOLINE_2(a, b, c, args...)
#undef TRAMPOLINE_PRIV(a, b, c, d, args...)
*/


//extern _IMPEXP_BE struct rgb_color ui_color__F11color_which(enum color_which which);

#define TRAMPOLINE_1(a, b, c, d, args...) { b, EMPTY_JUMPFRAME },
#define TRAMPOLINE_2(a, b, c, args...) { b, EMPTY_JUMPFRAME },
#define TRAMPOLINE_PRIV(a, b, c, d, args...) { b, EMPTY_JUMPFRAME },

static trampolist tList[] = {
#include "trampolist.h"
	{NULL, EMPTY_JUMPFRAME}
};

#undef TRAMPOLINE_1(a, b, c, d, args...)
#undef TRAMPOLINE_2(a, b, c, args...)
#undef TRAMPOLINE_PRIV(a, b, c, d, args...)

// the omnipresent call 0(ip) (well, in R5 at least =)
static const unsigned char nullcallbytes[5] = { 0xe8, 0x0, 0x0, 0x0, 0x0 };

void _init_libbe_trampolines(void)
{
	int i;
//	area_info ai;
	area_id aid;
	currentplugin = 0;
	// get aid of code segment for libbe
	aid = area_for(tList[0].orig);
//	get_area_info(area_for(tList[0].orig), &ai);
	// set code seg of libbe to read-write
	set_area_protection(aid, B_WRITE_AREA|B_READ_AREA);
	// same for us
	set_area_protection(area_for(__static_saved_prologues), B_WRITE_AREA|B_READ_AREA);

/*
	for (i = 0; tList[i].orig; i++) {
		char *p = (char *)tList[i].orig;
		char *dst = (char *)tList[i].hooked;
		int32 diff = dst - p - 5;
#ifdef DEBUG
		fprintf(stderr, "patching %p to %p...\n", p, dst);
#endif
		p[0] = 0xe9; // jump (near: 32b addr, relative)
		*(uint32 *)(&p[1]) = diff;
	}
*/
	for (i = 0; tList[i].orig; i++) {
		int j;
		int found = 0;
		unsigned char *p = (unsigned char *)tList[i].orig;

		// first find an instruction boundary in the prologue
		for (j = 0; !found && j < MAX_PROLOGUE - 2; j++) {
			if (!memcmp(&(p[j]), nullcallbytes, 5))
				found = 1;
#ifdef B_BEOS_VERSION_DANO
			if (p[j] == 0xe8 && p[j+2] == 0xff && p[j+3] == 0xff && p[j+4] == 0xff)
				found = 1;
#endif
			if (found)
				break;
		}
//found = 0;
		if (!found) {
#ifdef DEBUG
			fprintf(stderr, "libbehack: can't hook into func %i @%p !!!\n", i, p);
#endif
			continue;
		}
#ifdef DEBUG
		fprintf(stderr, "libbehack: copying prologue of func %i @%p, len %i\n", i, p, j);
#endif
		if (p[0] == 0xe9) { // the prologue begins with a jmp... looks like already patched
			fprintf(stderr, "from code section\n");
			fprintf(stderr, "%02x %02x %02x %02x -> %02x %02x %02x %02x\n", 
						__static_saved_prologues[MAX_PROLOGUE * i],
						__static_saved_prologues[MAX_PROLOGUE * i + 1],
						__static_saved_prologues[MAX_PROLOGUE * i + 2],
						__static_saved_prologues[MAX_PROLOGUE * i + 3],
						tList[i].original_prologue[0],
						tList[i].original_prologue[1],
						tList[i].original_prologue[2],
						tList[i].original_prologue[3]);
			// copy it from our own code segment where they were saved
			memcpy(tList[i].original_prologue, &__static_saved_prologues[MAX_PROLOGUE * i], j);
		} else {
			fprintf(stderr, "from libbe\n");
			fprintf(stderr, "%02x %02x %02x %02x -> %02x %02x %02x %02x\n", 
						p[0], p[1], p[2], p[3],
						tList[i].original_prologue[0],
						tList[i].original_prologue[1],
						tList[i].original_prologue[2],
						tList[i].original_prologue[3]);
			fprintf(stderr, "%02x %02x %02x %02x -> %02x %02x %02x %02x\n", 
						p[0], p[1], p[2], p[3],
						__static_saved_prologues[MAX_PROLOGUE * i],
						__static_saved_prologues[MAX_PROLOGUE * i + 1],
						__static_saved_prologues[MAX_PROLOGUE * i + 2],
						__static_saved_prologues[MAX_PROLOGUE * i + 3]);
			// copy the prologue to the struct
			memcpy(tList[i].original_prologue, p, j);
			// and to our own code segment for the next instances
			memcpy(&__static_saved_prologues[MAX_PROLOGUE * i], p, j);
		}

		// calculate the jumpback before hooking
		//                                            dest    - src                                    - sizeof(jmp near)
		//tList[i].backaddr = (void *)(unsigned char *)((p + j) - ((unsigned char *)&(tList[i].jmpback)) - 5);
		tList[i].backaddr = (void *)(unsigned char *)((p + j) - ((unsigned char *)&(tList[i].backaddr)) - 4);

		// patch the libbe prologue
#ifdef DEBUG
		fprintf(stderr, "libbehack: patching prologue of func %i @%p\n", i, p);
#endif
//		if (p[0] == 0xe9)
//			debugger("panic: already patched !"); // panic
		// we overwrite it after the 2nd application (at least in Dano) (no copy-on-write)
		// don't care
		p[0] = 0xe9; // jump (near: 32b addr, relative)
		//                   dest                              - src - sizeof(jmp near)
		*(uint32 *)(&p[1]) = ((unsigned char *)&(tList[i].nops)) - p - 5;
	}

	// handle special case: BApplication::-ReadyTo-Run(),
	// which we hook to be able to add the MessageFilter,
	// but isn't part of the public deal
	// -- it looks like it doesn't do anything, so just overwrite it with a jmp
	//unsigned char *p = (unsigned char *)ReadyToRun__12BApplication;
	//unsigned char *p = (unsigned char *)Run__12BApplication;
	
	//p[0] = 0xe9; // a jump
	tList[0].jmp = 0xe8; // a call
	//*(uint32 *)(&p[1]) = (uint32)(unsigned char *)(((unsigned char *)_init_app_msg_filter) - p - 5);
	tList[0].hooked = (void *)(unsigned char *)(((unsigned char *)_init_app_msg_filter) - ((unsigned char *)&(tList[0].hooked)) - 4);

	set_area_protection(area_for(__static_saved_prologues), B_READ_AREA);
	set_area_protection(aid, B_READ_AREA); // set back code seg of libbe to readonly
}

status_t switch_gui_hooks(int32 maxhooks, void **hooks)
{
	void volatile **pjump; // the pointer we want to modify
	void *pnew;
	int i, j;

	for (i = 0, j = PRIVATE_HOOK_COUNT; tList[j].orig && i < maxhooks; i++, j++) {
		pjump = (void volatile **)&(tList[j].hooked);
		pnew = NULL;
		if (hooks && hooks[i]) {
			pnew = (void *)(unsigned char *)(((unsigned char *)hooks[i]) - ((unsigned char *)&tList[j].hooked) - 4);
		}
#ifdef DEBUG
		fprintf(stderr, "libbehack: repatching func %i(%i) to %p\n", i, j, pnew);
#endif
		*pjump = pnew;
	}

	return B_OK;
}

status_t load_guiskin_plugin(const char *name)
{
	status_t err;
	image_id newplugin = 0;
	image_id oldplugin = 0;
	char buff[B_PATH_NAME_LENGTH];
	gui_hooklist_t *hooklist = NULL;
	gui_hooklist_t *(*gui_plugin_init_func)(uint32 version, status_t *err, void *trampolines);

	if (!name || name[0] == '\0') { // NULL means back to default look
		PRINT(("libbehack: setting default hooks\n"));
		err = switch_gui_hooks(NUMHOOKS, NULL);
		if (currentplugin) {
			PRINT(("libbehack: unloading oldaddon %ld\n", currentplugin));
			unload_add_on(currentplugin);
			currentplugin = 0;
		}
		return err;
	}

	strcpy(buff, "skinobe/");
	strncat(buff, name, B_PATH_NAME_LENGTH - 10);
	newplugin = load_add_on(buff);
	if (newplugin < B_OK)
		return newplugin;
	PRINT(("libbehack: loaded plugin '%s' (%ld)\n", buff, newplugin));
	err = get_image_symbol(newplugin, "gui_skin_plugin_init", B_SYMBOL_TYPE_TEXT, (void **)&gui_plugin_init_func);
	if (err < B_OK) {
		unload_add_on(newplugin);
		return err;
	}

	hooklist = gui_plugin_init_func(0x0000010b, &err, tList);
	if (hooklist == NULL) {
		unload_add_on(newplugin);
		return err;
	}

	//err = switch_gui_hooks(MIN(hooklist->numhooks, NUMHOOKS), hooklist->u.hooks);
	err = switch_gui_hooks(NUMHOOKS, hooklist->u.hooks);

	oldplugin = currentplugin;
	currentplugin = newplugin;

	if (oldplugin) {
		PRINT(("libbehack: unloading oldaddon %ld\n", oldplugin));
		unload_add_on(oldplugin);
	}

	return err;
}

#ifdef __cplusplus
}
#endif

