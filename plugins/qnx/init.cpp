#include <stdio.h>
#include <gui_skin_plugin.h>

const char gui_skin_plugin_description[] = "QNX Skin, (c) 2003, mmu_man";

gui_hooklist_t skin_hooks = { 6, 0, {NULL, BButton__Draw, BCheckBox__Draw, BRadioButton__Draw, NULL/*BMenuBar__Draw*/, BMenu__DrawBackground} };
//gui_hooklist_t skin_hooks = { 5, 0, {BButton__Draw, BCheckBox__Draw, BRadioButton__Draw, BMenuBar__Draw, BMenu__DrawBackground} };

struct trampolist *trampos;

gui_hooklist_t *gui_skin_plugin_init(uint32 version, status_t *err, void *trampolines)
{
	fprintf(stderr, "plugin qnx loaded\n");
	*err = B_OK;
	trampos = (struct trampolist *)trampolines;
	return &skin_hooks;
}

