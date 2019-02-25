#include <stdio.h>
#include <OS.h>
#define private public
#include <CheckBox.h>
#undef private
#include <gui_skin_plugin.h>

#include "osxstipple.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef B_BEOS_VERSION_DANO
//#define SWITCHST fChanged
//#define SWITCHST fState
#define SWITCHST IsPressed()
#else
#define SWITCHST fOutlined
#endif

void BCheckBox__Draw(BCheckBox *_this, BRect updateRect)
{
	puts("BCheckBox::Draw() hook called");

	// GonxCheckBox
//	_this->SetDrawingMode(B_OP_ALPHA);
	_this->SetFont(be_plain_font);
	_this->SetFontSize(10);
////
	rgb_color navCol = ui_color(B_KEYBOARD_NAVIGATION_COLOR);
	rgb_color ctlCol = {0, 0, 0, 255};
	font_height fh;
	
	//	DrawCheckBox();

	//Need to clean up this
	draw_osx_stipple(_this, updateRect);
	//_this->FillRect(updateRect, B_SOLID_LOW);
	BRect r,r2;
	r.top = (_this->Bounds().bottom / 2) - 6;
	r.bottom = (_this->Bounds().bottom / 2) + 6;
	r.right = _this->Bounds().left + 13;
	r.left = _this->Bounds().left + 1;

	// 3D border
	if (_this->IsEnabled())
		_this->SetHighColor(184,184,184);
	else
		_this->SetHighColor(tint_color(_this->ViewColor(), B_DARKEN_2_TINT));
	_this->StrokeRect(r);
	r.OffsetBySelf(1,1);
	if (_this->IsEnabled())
		_this->SetHighColor(255,255,255);
	else
		_this->SetHighColor(tint_color(_this->ViewColor(), B_LIGHTEN_2_TINT));
	_this->StrokeRect(r);
	r.right--;
	r.bottom--;

	//Background in checkbox
	_this->SetPenSize(1.0);
	if (_this->IsEnabled())
		_this->SetHighColor(255,255,255);
	else
		_this->SetHighColor(tint_color(_this->ViewColor(), B_LIGHTEN_1_TINT));
	_this->FillRect(r);

	//Outer frame
	if (_this->IsEnabled())
		_this->SetHighColor(60,60,60);
	else
		_this->SetHighColor(tint_color(_this->ViewColor(), B_DARKEN_1_TINT));
	_this->StrokeRect(r);
		
	//Checkbox
//	if(_this->Value() > 1) // down
	if(_this->SWITCHST) // down
	{
		_this->SetPenSize(2.0);
		_this->SetHighColor(tint_color(ctlCol, B_LIGHTEN_2_TINT));
		_this->StrokeLine(BPoint(r.left+3,r.top+3),BPoint(r.right-3,r.bottom-3));
		_this->StrokeLine(BPoint(r.right-3,r.top+3),BPoint(r.left+3,r.bottom-3));
		_this->SetPenSize(1.0);
	}

	else if(_this->Value()) // checked
	{
		_this->SetPenSize(2.5);
		_this->SetHighColor(tint_color(ctlCol, B_LIGHTEN_2_TINT));
		_this->StrokeLine(BPoint(r.left+2,r.top+2),BPoint(r.right-2,r.bottom-2));
		_this->StrokeLine(BPoint(r.right-2,r.top+2),BPoint(r.left+2,r.bottom-2));
		_this->SetPenSize(1.0);
		if (_this->IsEnabled())
			_this->SetHighColor(ctlCol);
		else
			_this->SetHighColor(tint_color(ctlCol, B_LIGHTEN_2_TINT));
		_this->StrokeLine(BPoint(r.left+2,r.top+2),BPoint(r.right-2,r.bottom-2));
		_this->StrokeLine(BPoint(r.right-2,r.top+2),BPoint(r.left+2,r.bottom-2));
	} else {
		if (_this->IsEnabled())
			_this->SetHighColor(tint_color(_this->ViewColor(), B_DARKEN_1_TINT));
		else
			_this->SetHighColor(tint_color(ctlCol, B_LIGHTEN_2_TINT));
		_this->StrokeRect(r.InsetByCopy(2,2));
	}


	//	Text
	if (_this->Label()) {
		be_plain_font->GetHeight(&fh);
	
		if (_this->IsEnabled()) {
			_this->MovePenTo(_this->Bounds().left + 20,(_this->Bounds().bottom/2)+(fh.ascent/2)-1);
			_this->SetHighColor(0,0,0);
			_this->DrawString(_this->Label());
		} else {
			_this->MovePenTo(_this->Bounds().left + 21,(_this->Bounds().bottom/2)+(fh.ascent/2));
			_this->SetHighColor(tint_color(_this->ViewColor(), B_LIGHTEN_2_TINT));
			_this->DrawString(_this->Label());
			_this->MovePenTo(_this->Bounds().left + 20,(_this->Bounds().bottom/2)+(fh.ascent/2)-1);
			_this->SetHighColor(tint_color(_this->ViewColor(), B_DARKEN_2_TINT));
			_this->DrawString(_this->Label());
		}
	}
			
	if(_this->IsFocus())
	{
		_this->SetHighColor(navCol);
		_this->StrokeLine(BPoint( ( _this->Bounds().left + 20 ), ( (_this->Bounds().bottom/2)+fh.ascent - 4) ),
				BPoint( ( _this->Bounds().left + 20 + be_plain_font->StringWidth(_this->Label()) ) ,( ( _this->Bounds().bottom/2 ) + fh.ascent - 4) ) );
		_this->SetHighColor(255,255,255);
		_this->StrokeLine(BPoint( ( _this->Bounds().left + 20 ), ( (_this->Bounds().bottom/2)+fh.ascent - 3) ),
				BPoint( ( _this->Bounds().left + 20 + be_plain_font->StringWidth(_this->Label()) ) ,( ( _this->Bounds().bottom/2 ) + fh.ascent - 3) ) );
	}
}

#ifdef __cplusplus
}
#endif

