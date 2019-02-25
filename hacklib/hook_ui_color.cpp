#include <stdio.h>
#include <OS.h>
#include <InterfaceDefs.h>

#ifdef __cplusplus
extern "C" {
#endif

static const rgb_color gonxColors[10] = 
{
{0, 0, 0, 255}, // null color
{239, 235, 231, 255}, // B_PANEL_BACKGROUND_COLOR
{239, 235, 231, 255}, // B_MENU_BACKGROUND_COLOR
{255, 203, 0, 255}, // B_WINDOW_TAB_COLOR
//{115, 120, 184, 255}, // B_KEYBOARD_NAVIGATION_COLOR
{80, 114, 154, 255}, // B_KEYBOARD_NAVIGATION_COLOR
{51, 102, 152, 255}, // B_DESKTOP_COLOR
{247, 247, 247, 255}, // B_MENU_SELECTION_BACKGROUND_COLOR
{0, 0, 30, 255}, // B_MENU_ITEM_TEXT_COLOR
{0, 0, 50, 255}, // B_MENU_SELECTED_ITEM_TEXT_COLOR
{0, 255, 255, 255} // 
};

rgb_color hooked_ui_color__F11color_which(color_which which)
{
	int iwhich = *(int *)&which;
	puts("ui_color() hook called");
	if (iwhich < 0 || iwhich > 9)
		iwhich = 0;
	return gonxColors[iwhich];
}

#ifdef __cplusplus
}
#endif

