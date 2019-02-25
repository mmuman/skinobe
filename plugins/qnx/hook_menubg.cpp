#include <stdio.h>
#include <OS.h>
#define private public
#include <Menu.h>
#undef private
#include <gui_skin_plugin.h>

#include "gradient.h"

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

	rgb_color oldHigh = _this->HighColor();
	rgb_color oldLow = _this->LowColor();
//	_this->PushState();

	// border
	r = bounds;
	_this->SetHighColor(lightBorderCol);
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
	_this->SetHighColor(oldHigh);
	_this->SetLowColor(oldLow);
return;
#if 0
	// the text
	be_plain_font->GetHeight(&fh);
	_this->SetHighColor(textCol);

	BPoint pen((bounds.right/2)-((be_plain_font->StringWidth(_this->Label())/2)),(bounds.bottom/2)+(fh.ascent/2) - (!_this->fSelected? 1:0));
	if (!_this->IsEnabled()) {
		_this->SetHighColor(lightBorderCol);
		pen += BPoint(1, 1);
	}
	_this->MovePenTo(pen);
	_this->DrawString(_this->Label());
	if (!_this->IsEnabled()) {
		_this->SetHighColor(borderCol1);
		pen -= BPoint(1, 1);
		_this->MovePenTo(pen);
		_this->DrawString(_this->Label());
	}
	
/*
//	if(BControl::IsFocus() && enabled) {
	if((_this->IsFocus() && _this->IsEnabled()) || _this->fDrawAsDefault) {
		rgb_color focusCol = ::ui_color(B_KEYBOARD_NAVIGATION_COLOR);
		if(!_this->IsFocus())
			focusCol = tint_color(focusCol, B_LIGHTEN_2_TINT);
//		_this->SetHighColor(80,114,154);
		_this->SetHighColor(focusCol);
		BPoint p1,p2;
		p1.x = (bounds.right/2)-((be_plain_font->StringWidth(_this->Label())/2))-1;
		p1.y = (bounds.bottom/2)+(fh.ascent/2)+1;
		p2.x =  p1.x + be_plain_font->StringWidth(_this->Label());
		p2.y = p1.y;
		_this->StrokeLine(p1,p2);
	}
*/
#endif
#if 0
		if (_this->fDrawAsDefault)
		{
			//_this->DrawDefault(updateRect, false/*_this->IsEnabled()*/);
			rgb_color focusCol = ui_color(B_KEYBOARD_NAVIGATION_COLOR);

		}
#endif
//	BControl::Draw(updateRect);
//	BControl *bcontrol = dynamic_cast<BControl *>(_this);
//	(dynamic_cast<BControl *>(_this))->Draw(updateRect);
//	if (bcontrol)
//		bcontrol->Draw(updateRect);

	_this->PopState();

}

#ifdef __cplusplus
}
#endif

