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
	rgb_color col = {194, 205, 224, 255};
#ifdef B_BEOS_VERSION_DANO
	col = ui_color(B_CONTROL_HIGHLIGHT_COLOR);
#endif
	BRect r;
	font_height fh;
	puts("BBox::Draw() hook called");

	_this->PushState();
	
	r = _this->Bounds();
	_this->SetHighColor(col);
	
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
			_this->SetPenSize(2);
			_this->StrokeRoundRect(r, 7, 7);
			break;

		case B_PLAIN_BORDER:
			_this->StrokeRoundRect(r, 7, 7);
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
		
		/*draw_osx_stipple(_this, BRect(6.0f, 1.0f, 12.0f + _this->StringWidth(_this->fLabel),
		(float)ceil(fh.ascent + fh.descent)));*/
		_this->FillRect(BRect(6.0f, 1.0f, 12.0f + _this->StringWidth(_this->fLabel),
		(float)ceil(fh.ascent + fh.descent)), B_SOLID_LOW);
		
		//Sets the Text color to Black
		_this->SetHighColor(kTextColor);
		_this->DrawString(_this->fLabel, BPoint(10.0f, (float)ceil(fh.ascent - fh.descent) + 1.0f ));
	}
	_this->PopState();

}

#ifdef __cplusplus
}
#endif

