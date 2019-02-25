#include <stdio.h>
#include <OS.h>
#define private public
#include <RadioButton.h>
#undef private
#include <Font.h>

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

extern int32 BApp_created;

void hooked_Draw__12BRadioButtonG5BRect(BRadioButton *_this, BRect updateRect)
{
	puts("BRadioButton::Draw() hook called");
	
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
	_this->DrawString(_this->Label(), 50/*_this->fCachedWidth*/, _this->Bounds().LeftBottom()+=BPoint(5.0, -5.0));
	_this->PopState();
#endif

	BFont font;
	_this->GetFont(&font);
	font_height fh;
	font.GetHeight(&fh);

	///Create/define the rects
	BRect r, r2;	
	r.top = (_this->Bounds().bottom / 2) - 5;
	r.bottom = (_this->Bounds().bottom / 2) + 5;
	r.right = _this->Bounds().left + 16;
	r.left = _this->Bounds().left + 6;
	
	//Shadow
	r2 = r;
	r2.top += 2;
	r2.bottom += 2;
	r2.left += 2;
	r2.right += 2;
	_this->SetPenSize(1.0);
	_this->SetHighColor(140,140,121,90);

	r2.top -= 1;
	r2.bottom -= 1;
	r2.left -= 1;
	r2.right -= 1;
	_this->SetPenSize(1.0);
	_this->SetHighColor(140,140,121,180);
	_this->FillRoundRect(r2, 6, 6);

	//Background in RadioButton
	_this->SetPenSize(1.0);
	_this->SetHighColor(255,255,255);	
	_this->FillRoundRect(r, 6, 6);

	//Outer frame
	_this->SetHighColor(140,140,121);
	_this->StrokeRoundRect(r, 6, 6);
		
	r.InsetBy(4, 4);
		
	if (!_this->IsEnabled())
	{
		r.InsetBy(1,1);
	}
	
	if (_this->Value() == B_CONTROL_ON)
	{
		_this->SetHighColor(80,114,154);
			
		_this->FillEllipse(r);
		_this->SetHighColor(157,179,204);
		r.InsetBy(-1, -1);
		_this->StrokeEllipse(r);
		_this->SetHighColor(1,1,1);
	}	
	
	if (_this->IsEnabled())
		_this->SetHighColor(::ui_color(B_MENU_ITEM_TEXT_COLOR));
	else
		_this->SetHighColor(::tint_color(::ui_color(B_MENU_ITEM_TEXT_COLOR), B_DISABLED_MARK_TINT));
	//Draws the String
	_this->MovePenTo(_this->Bounds().left + 25,(_this->Bounds().bottom/2)+(fh.ascent/2));
	_this->DrawString(_this->Label());
	
	if (_this->SWITCHST)
	{	//When we press we see a small RoundRect Before we release the button
		_this->SetHighColor(157,179,204);
		r.InsetBy(0,0);
		_this->FillRoundRect(r, 6, 6);
	}
	

}

#ifdef __cplusplus
}
#endif

