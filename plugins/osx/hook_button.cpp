#include <stdio.h>
#include <OS.h>
#define private public
#include <Button.h>
#undef private
#include <gui_skin_plugin.h>

#include "gradient.h"

#ifdef __cplusplus
extern "C" {
#endif

void BButton__Draw(BButton *_this, BRect updateRect)
{
	puts("BButton::Draw() hook called");

	// GonxButton
	font_height fh;
	BRect bounds = _this->Bounds();
	if (_this->IsDefault())
		bounds.InsetBySelf(3,3);
	bounds.bottom -=1;
	bounds.right -= 1;
	BRect r;
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

	rgb_color gradCol1, gradCol2;
#ifdef B_BEOS_VERSION_DANO
	gradCol1 = tint_color(ui_color(B_CONTROL_BACKGROUND_COLOR), B_LIGHTEN_2_TINT);
	gradCol2 = tint_color(ui_color(B_CONTROL_BACKGROUND_COLOR), B_DARKEN_2_TINT);
#else
	gradCol1 = tint_color(ui_color(B_MENU_BACKGROUND_COLOR), B_LIGHTEN_2_TINT);
	gradCol2 = tint_color(ui_color(B_MENU_BACKGROUND_COLOR), B_DARKEN_2_TINT);
#endif

	rgb_color selectedBorderCol = {154, 152, 248, 255};
	selectedBorderCol = ::ui_color(B_KEYBOARD_NAVIGATION_COLOR);

	_this->PushState();

	// border
	r = bounds;
	_this->SetHighColor((_this->Value())?borderCol1:lightBorderCol);
	r.left += 2;
	r.top += 2;
	_this->StrokeRect(r);

	r.left -= 1;
	r.top -= 1;

	BRect r2(r);
	r2.OffsetBy(-1, -1);
	_this->SetHighColor((_this->Value())?lightBorderCol:borderCol1);
	if (_this->Value()) {
//		r2 = r;
		r2.OffsetBy(1, 1);
	}
	_this->StrokeRect(r2);

	//r2.OffsetBy(1, 1);
	_this->SetHighColor(_this->IsFocus()?selectedBorderCol:borderCol2);
	_this->StrokeRect(r);

	r.InsetBy(2, 2);
	// the gradient filling
	draw_qnx_gradiant(_this, r, true, gradCol1, gradCol2);

	// the text
	bounds = _this->Bounds();
	be_plain_font->GetHeight(&fh);
	_this->SetHighColor(textCol);

	BPoint pen((bounds.right/2)-((be_plain_font->StringWidth(_this->Label())/2)),(bounds.bottom/2)+(fh.ascent/2) - (!_this->Value()? 1:0));
	if (!_this->IsEnabled()) {
		_this->SetHighColor(lightBorderCol);
		pen += BPoint(1, 1);
	}
	_this->MovePenTo(pen);
	if (_this->Label())
		_this->DrawString(_this->Label());
	if (!_this->IsEnabled()) {
		_this->SetHighColor(borderCol1);
		pen -= BPoint(1, 1);
		_this->MovePenTo(pen);
		if (_this->Label())
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

