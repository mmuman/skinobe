#include <stdio.h>
#include <OS.h>
#include <InterfaceDefs.h>
#define private public
#include <Box.h>
#undef private

#include "osxstipple.h"

#ifdef __cplusplus
extern "C" {
#endif

void BBox__Draw(BBox *_this, BRect updateRect)
{
	rgb_color cShadow = {180,180,180,255};
	rgb_color cShine = {255,255,255,255};
#ifdef B_BEOS_VERSION_DANO
	cShadow = ui_color(B_SHADOW_COLOR);
	cShine = ui_color(B_SHINE_COLOR);
#endif
	BRect r;
	font_height fh;
	puts("BBox::Draw() hook called");

	_this->PushState();
	_this->SetHighColor(0,0,0);
	
	r = _this->Bounds();
	
	draw_osx_stipple(_this, updateRect);
	_this->SetHighColor(cShadow);
	
	// center the top line on the text
	if (_this->fLabel) {
		_this->GetFontHeight(&fh);
		r.top += fh.ascent / 2;
	}
	if (_this->fLabelView) {
		r.top += _this->fLabelView->Bounds().Height() / 2;
	}
	// draw the box
	switch (_this->Border())
	{
		case B_FANCY_BORDER:
			//_this->DrawFancy();
			r.right--;
			r.bottom--;
			_this->StrokeRect(r);
			r.OffsetBySelf(1,1);
			_this->SetHighColor(cShine);
			_this->StrokeRect(r);
			break;

		case B_PLAIN_BORDER:
			//_this->DrawPlain();
			_this->StrokeRect(r);
			break;

		default:
			break;
	}
	if (_this->fLabel)
	{
		rgb_color kTextColor = {0,0,0,255};
#ifdef B_BEOS_VERSION_DANO
		kTextColor = ui_color(B_PANEL_TEXT_COLOR);
#endif
		
		//_this->SetLowColor(_this->Parent()->ViewColor());
		_this->SetLowColor(_this->ViewColor());
		
		draw_osx_stipple(_this, BRect(6.0f, 1.0f, 12.0f + _this->StringWidth(_this->fLabel),
		(float)ceil(fh.ascent + fh.descent)));
		/*_this->FillRect(BRect(6.0f, 1.0f, 12.0f + _this->StringWidth(_this->fLabel),
		(float)ceil(fh.ascent + fh.descent)), B_SOLID_LOW);*/
		
		//Sets the Text color to Black
		_this->SetHighColor(kTextColor);
		_this->DrawString(_this->fLabel, BPoint(10.0f, (float)ceil(fh.ascent - fh.descent) + 1.0f ));
	}
	_this->PopState();

#if 0
	// GonxCheckBox
//	_this->SetDrawingMode(B_OP_ALPHA);
	_this->SetFont(be_plain_font);
	_this->SetFontSize(10);
////

	font_height fh;
	
	//	DrawCheckBox();

	//Need to clean up this
	_this->FillRect(updateRect, B_SOLID_LOW);
	BRect r,r2;
	//r.top = (_this->Bounds().bottom / 2) - 5;
	//r.bottom = (_this->Bounds().bottom / 2) + 5;
	//r.right = _this->Bounds().left + 16;
	//r.left = _this->Bounds().left + 6;
	r.top = (_this->Bounds().bottom / 2) - 6;
	r.bottom = (_this->Bounds().bottom / 2) + 4;
	r.right = _this->Bounds().left + 11;
	r.left = _this->Bounds().left + 1;


	//Shadow
	r2 = r;
	r2.top += 2;
	r2.bottom += 2;
	r2.left += 2;
	r2.right += 2;
	_this->SetPenSize(1.0);
	_this->SetHighColor(140,140,121,90);
	_this->StrokeLine(BPoint(r2.right,r2.top),BPoint(r2.right,r2.bottom-1));
	_this->StrokeLine(BPoint(r2.left,r2.bottom),BPoint(r2.right-1,r2.bottom));

	r2.top -= 1;
	r2.bottom -= 1;
	r2.left -= 1;
	r2.right -= 1;
	_this->SetPenSize(1.0);
	_this->SetHighColor(140,140,121,180);
	_this->FillRect(r2);

	//Background in checkbox
	_this->SetPenSize(1.0);
	_this->SetHighColor(255,255,255);	
	_this->FillRect(r);

	//Outer frame
	_this->SetHighColor(140,140,121);
	_this->StrokeRect(r);
#endif
		
	//Checkbox
//	if(_this->Value() > 1) // down
#if 0
	if(_this->SWITCHST) // down
	{
		_this->SetPenSize(2.0);
		_this->SetHighColor(80,114,154);
		_this->StrokeLine(BPoint(r.left+3,r.top+3),BPoint(r.right-3,r.bottom-3));
		_this->StrokeLine(BPoint(r.right-3,r.top+3),BPoint(r.left+3,r.bottom-3));
	}

	else if(_this->Value()) // checked
	{
		_this->SetPenSize(2.5);
		_this->SetHighColor(80,114,154);
		_this->StrokeLine(BPoint(r.left+2,r.top+2),BPoint(r.right-2,r.bottom-2));
		_this->StrokeLine(BPoint(r.right-2,r.top+2),BPoint(r.left+2,r.bottom-2));
	}

#endif
#if 0
	//	Text
	_this->SetHighColor(0,0,0);
	be_plain_font->GetHeight(&fh);
	
	//_this->MovePenTo(_this->Bounds().left + 25,(_this->Bounds().bottom/2)+(fh.ascent/2));
	_this->MovePenTo(_this->Bounds().left + 20,(_this->Bounds().bottom/2)+(fh.ascent/2)-1);
	
	if (_this->Label())
		_this->DrawString(_this->Label());
	if(_this->IsFocus())
	{
		_this->SetPenSize(1.0);
		_this->SetHighColor(80,114,154);
		_this->StrokeLine(BPoint( ( _this->Bounds().left + 27 ), ( (_this->Bounds().bottom/2)+fh.ascent - 4) ),
					BPoint( ( _this->Bounds().left + 23 + be_plain_font->StringWidth(_this->Label()) ) ,( ( _this->Bounds().bottom/2 ) + fh.ascent - 4) ) );
	}
#endif
}

#ifdef __cplusplus
}
#endif

