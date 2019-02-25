#include <stdio.h>
#include <OS.h>
#define private public
#include <Button.h>
#undef private
#include <gui_skin_plugin.h>

//void hooked_Draw__7BButtonG5BRect(BButton *_this, BRect updateRect)
void BButton__Draw(BButton *_this, BRect updateRect)
{
	pattern drawingPattern = B_SOLID_HIGH;
	puts("BButton::Draw() hook called");
	_this->PushState();
	_this->SetLowColor(255, 255, 255);
	if (!_this->IsEnabled())
		drawingPattern = B_MIXED_COLORS;
	if (_this->Value())
		_this->FillRect(_this->Bounds(), drawingPattern);
	else if (_this->IsDefault()) {
		_this->FillRect(_this->Bounds(), drawingPattern);
		_this->FillRect(_this->Bounds().InsetBySelf(5, 5), B_SOLID_LOW);
	} else {
		_this->FillRect(_this->Bounds(), B_SOLID_LOW);
		_this->StrokeRect(_this->Bounds(), drawingPattern);
	}
	printf("label = %s, len = %ld\n", _this->Label(), _this->fCachedWidth);
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
