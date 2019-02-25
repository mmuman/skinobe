#include <stdio.h>
#include <gui_skin_plugin.h>

const char gui_skin_plugin_description[] = "Gonx Skin, (c) 2003, Konrad, mmu_man";

gui_hooklist_t skin_hooks = { 4, 0, {NULL, BButton__Draw, BCheckBox__Draw, BRadioButton__Draw} };

gui_hooklist_t *gui_skin_plugin_init(uint32 version, status_t *err, void *)
{
	fprintf(stderr, "plugin gonx loaded\n");
	*err = B_OK;
	return &skin_hooks;
}

