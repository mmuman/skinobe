#include <stdio.h>
#include <View.h>
#include <Window.h>
#include "osxstipple.h"

rgb_color kBgOSX = {250,250,250,255};
rgb_color kBgOSXL = {255, 255, 255,255};
rgb_color kBgOSXD = {235, 235, 235, 255};

/*
rgb_color my_tint_color(rgb_color col, float tint)
{
	rgb_color c;
	float v;
	v = (col.red + (1.0-tint) * (255 - col.red));
	c.red = (uint8)MAX(MIN(v, 255), 0);
	v = (col.green + (1.0-tint) * (255 - col.green));
	c.green = (uint8)MAX(MIN(v, 255), 0);
	v = (col.blue + (1.0-tint) * (255 - col.blue));
	c.blue = (uint8)MAX(MIN(v, 255), 0);
	return c;
}
*/
rgb_color offset_color(rgb_color col, float tint)
{
	rgb_color c;
	float v;
	c.red = (uint8)MAX(MIN(col.red+tint, 255), 0);
	c.green = (uint8)MAX(MIN(col.green+tint, 255), 0);
	c.blue = (uint8)MAX(MIN(col.blue+tint, 255), 0);
	return c;
}

void draw_osx_stipple(BView *view, BRect frame)
{
	long yoff = 0L;
	BPoint p(0,0);
#ifdef B_BEOS_VERSION_DANO
	kBgOSX = ui_color(B_PANEL_BACKGROUND_COLOR);
	//kBgOSXL = tint_color(kBgOSX, B_LIGHTEN_1_TINT);
	//kBgOSXD = tint_color(kBgOSX, B_DARKEN_1_TINT);
	kBgOSXL = offset_color(kBgOSX, 10);
	kBgOSXD = offset_color(kBgOSX, -10);
#endif
	view->ConvertToScreen(&p);
	if (view->Window()) {
		p -= view->Window()->Frame().LeftTop();
		yoff = (long)p.y;
		yoff %= 4;
	}
	view->PushState();
	view->SetHighColor(kBgOSX);
	view->FillRect(frame);
	int i = (int)((frame.top / 4) * 4);
	view->BeginLineArray((frame.bottom - frame.top + 4) / 2);
	for (; i <= frame.bottom; i++) {
		if (i%4 == ((4-yoff)%4)) {
			view->AddLine(BPoint(frame.left, i), BPoint(frame.right, i), kBgOSXL);
		} else if (i%4 == ((4+2-yoff)%4)) {
			view->AddLine(BPoint(frame.left, i), BPoint(frame.right, i), kBgOSXD);
		}
		//view->AddLine(BPoint(frame.left, i), BPoint(frame.right, i), ui_color(B_MENU_BACKGROUND_COLOR));
	}
	view->EndLineArray();
	view->PopState();
}
