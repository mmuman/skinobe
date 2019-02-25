#include <stdio.h>
#include <OS.h>
#define private public
#include <CheckBox.h>
#undef private

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
#if 0
	_this->PushState();
	if (_this->Value())
		_this->FillRect(_this->Bounds()/*updateRect*/);
	else {
		_this->FillRect(_this->Bounds()/*updateRect*/, B_SOLID_LOW);
		_this->StrokeRect(_this->Bounds()/*updateRect*/);
	}
	printf("label = %s, len = %ld\n", _this->Label(), _this->fCachedWidth);
	_this->SetHighColor(0, 0, 255);
	if (_this->Label())
		_this->DrawString(_this->Label(), 50/*_this->fCachedWidth*/, _this->Bounds().LeftBottom()+=BPoint(5.0, -5.0));
	_this->PopState();
#endif

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
		
	//Checkbox
//	if(_this->Value() > 1) // down
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
}

#ifdef __cplusplus
}
#endif

