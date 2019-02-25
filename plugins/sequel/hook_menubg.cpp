#include <stdio.h>
#include <OS.h>
#define private public
#include <Menu.h>
#undef private
#include <gui_skin_plugin.h>

#include "osxstipple.h"

#ifdef __cplusplus
extern "C" {
#endif

//extern void Draw__5BMenuG5BRect(BMenu *_this, BRect updateRect);

void BMenu__DrawBackground(BMenu *_this, BRect updateRect)
{
	puts("BMenu::DrawBackground() hook called");

	// GonxButton
	font_height fh;
	BRect r;
	BRect bounds = _this->Bounds();
	bounds.right -= 1;
//	bounds.InsetBy(1, 1);
//	bounds.left = _this->Divider();
//	rgb_color borderCol1, borderCol2, selectedBorderCol, lightBorderCol, textCol, underlineCol1, underlineCol2;
	_this->PushState();


#ifdef B_BEOS_VERSION_DANO
	rgb_color borderCol2 = ::ui_color(B_CONTROL_BORDER_COLOR);
	rgb_color textCol = ::ui_color(B_CONTROL_TEXT_COLOR);
#else
	rgb_color borderCol2 = {72, 72, 72, 255};
	rgb_color textCol = {0, 0, 0, 255};
#endif
	rgb_color lightBorderCol = {248, 252, 248, 255};
	rgb_color borderCol1 = {176, 176, 176, 255};
	rgb_color underlineCol1 = {64, 69, 64, 255};
	rgb_color underlineCol2 = {240, 244, 240, 255};
	//selectedBorderCol = ::ui_color(B_KEYBOARD_NAVIGATION_COLOR);
	rgb_color selectedBorderCol = {154, 152, 248, 255};

	rgb_color gradCol1, gradCol2;
	gradCol1 = tint_color(ui_color(B_MENU_BACKGROUND_COLOR), B_LIGHTEN_2_TINT);
	gradCol2 = tint_color(ui_color(B_MENU_BACKGROUND_COLOR), B_DARKEN_2_TINT);

//	rgb_color oldHigh = _this->HighColor();
//	rgb_color oldLow = _this->LowColor();

	// border
	r = bounds;
	updateRect.left = _this->Bounds().left;
	updateRect.right = _this->Bounds().right + 5.0;
	
	draw_osx_stipple(_this, updateRect);
#if 0
	_this->SetHighColor(250,250,250);
	_this->FillRect(updateRect);
	int i = (int)((updateRect.top / 4) * 4);
	_this->BeginLineArray((updateRect.bottom - updateRect.top + 4) / 2);
	for (; i <= updateRect.bottom; i++) {
		if (i%4 == 0) {
			rgb_color c = {255, 255, 255, 255};
			_this->AddLine(BPoint(updateRect.left, i), BPoint(updateRect.right, i), c);
		} else if (i%4 == 2) {
			rgb_color c = {235, 235, 235, 255};
			_this->AddLine(BPoint(updateRect.left, i), BPoint(updateRect.right, i), c);
		}
		//_this->AddLine(BPoint(updateRect.left, i), BPoint(updateRect.right, i), ui_color(B_MENU_BACKGROUND_COLOR));
	}
	_this->EndLineArray();
#endif

#if 0
//	r.left += 1;
//	r.top += 1;
	r.right -= 1;
	r.bottom -= 1;
//	_this->StrokeRect(r);

	r.OffsetBy(1, 1);
	_this->SetHighColor(borderCol1);
//	_this->StrokeRect(r);
	
	// the gradient filling
	//draw_qnx_gradiant(_this, bounds.InsetBySelf(1, 1), false);
	//draw_qnx_gradiant(_this, updateRect.InsetBySelf(1, 1), false);
	updateRect.left = _this->Bounds().left;
	updateRect.right = _this->Bounds().right + 5.0;
	draw_qnx_gradiant(_this, updateRect, false, gradCol1, gradCol2, false);
//_this->PopState();
//	_this->SetLowColor(B_TRANSPARENT_32_BIT);
//	Draw__5BMenuG5BRect(_this, updateRect);
#endif
//	_this->SetHighColor(oldHigh);
//	_this->SetLowColor(oldLow);
	_this->PopState();
return;


}

#ifdef __cplusplus
}
#endif

