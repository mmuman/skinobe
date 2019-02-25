#include <stdio.h>
#include <OS.h>
#define private public
#include <RadioButton.h>
#undef private
#include <Font.h>
#include <gui_skin_plugin.h>

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
	
	pattern drawingPattern = B_SOLID_HIGH;
	puts("BButton::Draw() hook called");
	_this->PushState();
	_this->SetLowColor(255, 255, 255);
	if (!_this->IsEnabled())
		drawingPattern = B_MIXED_COLORS;
	if (_this->Value())
		_this->FillRect(_this->Bounds(), drawingPattern);
	else {
		_this->FillRect(_this->Bounds(), B_SOLID_LOW);
		_this->StrokeRect(_this->Bounds(), drawingPattern);
	}
//	printf("label = %s\n", _this->Label());
	font_height fh;
	_this->GetFontHeight(&fh);
	if (_this->Value())
		_this->SetHighColor(255, 255, 255);
	else
		_this->SetHighColor(0, 0, 0);
	BPoint pen((_this->Bounds().right/2)-((_this->StringWidth(_this->Label())/2)),(_this->Bounds().bottom/2)+(fh.ascent/2) - (!_this->Value()? 1:0));
	_this->MovePenTo(pen);
	if (_this->Label())
		_this->DrawString(_this->Label());
	if (_this->IsFocus()) {
		_this->MovePenBy(0, 2);
//		pen.x = _this->Bounds().right - pen.x;
		pen.y += 2;
		_this->StrokeLine(pen);
	}

	
//	_this->DrawString(_this->Label(), 50/*_this->fCachedWidth*/, _this->Bounds().LeftBottom()+=BPoint(5.0, -5.0));
	_this->PopState();
}

