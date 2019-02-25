#include <stdio.h>
#include <OS.h>
#define private public
#include <RadioButton.h>
#undef private
#include <Font.h>
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

void BRadioButton__Draw(BRadioButton *_this, BRect updateRect)
{
	puts("BRadioButton::Draw() hook called");
	
	BFont font;
	_this->GetFont(&font);
	font_height fh;
	font.GetHeight(&fh);

	rgb_color navCol = ui_color(B_KEYBOARD_NAVIGATION_COLOR);
	rgb_color ctlCol = {60, 60, 60, 255};

	draw_osx_stipple(_this, updateRect);
	//_this->FillRect(updateRect, B_SOLID_LOW);
	
	///Create/define the rects
	BRect r, r2;	
	r.top = (_this->Bounds().bottom / 2) - 5;
	r.bottom = (_this->Bounds().bottom / 2) + 6;
	r.right = _this->Bounds().left + 12;
	r.left = _this->Bounds().left + 1;
	
	r.InsetBySelf(1,1);
	
	if (_this->IsEnabled()) {
		rgb_color col = {255,255,255,255};
		r2 = r;
		r2.right--;
		r2.bottom--;
		r2.OffsetBySelf(1,1);
		_this->SetHighColor(tint_color(ctlCol, B_LIGHTEN_1_TINT));
		_this->FillEllipse(r2);

		r2.OffsetBySelf(-1,-1);
		_this->SetHighColor(col);
		_this->FillEllipse(r2);
		col = tint_color(col, B_DARKEN_1_TINT);
		_this->SetHighColor(col);
		r2.left+=1;	r2.top+=1;
		_this->FillEllipse(r2);
		col = tint_color(col, B_DARKEN_1_TINT);
		_this->SetHighColor(col);
		r2.left+=2;	r2.top+=2;
		_this->FillEllipse(r2);
	} else {
		_this->SetHighColor(tint_color(_this->ViewColor(), B_LIGHTEN_2_TINT));
		_this->FillEllipse(r);
	}
		
	if (_this->IsEnabled())
		_this->SetHighColor(60,60,60);
	else
		_this->SetHighColor(tint_color(_this->ViewColor(), B_DARKEN_2_TINT));
	_this->StrokeEllipse(r.InsetByCopy(-1,-1));
	

	r.InsetBySelf(2,2);

	
	if (_this->Value() == B_CONTROL_ON)
	{
		if (_this->IsEnabled())
			_this->SetHighColor(ctlCol);
		else
			_this->SetHighColor(tint_color(_this->ViewColor(), B_DARKEN_2_TINT));
		_this->FillEllipse(r);
		_this->SetHighColor(tint_color(_this->HighColor(), B_LIGHTEN_1_TINT));
		_this->StrokeEllipse(r);
	}	
	
	if (_this->SWITCHST)
	{	//When we press we see a small RoundRect Before we release the button
		_this->SetHighColor(ctlCol);
		r.InsetBySelf(2,2);
		_this->FillEllipse(r);
	}
	
	//Draws the String
/*	_this->MovePenTo(_this->Bounds().left + 25,(_this->Bounds().bottom/2)+(fh.ascent/2));
	if (_this->Label())
		_this->DrawString(_this->Label());
*/
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

