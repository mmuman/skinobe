#include <stdio.h>
#include <gui_skin_plugin.h>

const char gui_skin_plugin_description[] = "Atari ST GEM Skin, (c) 2003, mmu_man";

gui_hooklist_t skin_hooks = { 7, 0, {NULL, BButton__Draw, BCheckBox__Draw, BRadioButton__Draw, NULL, NULL, BBox__Draw} };

gui_hooklist_t *gui_skin_plugin_init(uint32 version, status_t *err, void *)
{
	fprintf(stderr, "plugin gem loaded\n");
	*err = B_OK;
	return &skin_hooks;
}

