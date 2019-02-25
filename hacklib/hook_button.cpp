#include <stdio.h>
#include <OS.h>
#define private public
#include <Button.h>
#undef private

#ifdef __cplusplus
extern "C" {
#endif

extern int32 BApp_created;

void hooked_Draw__7BButtonG5BRect(BButton *_this, BRect updateRect)
{
	puts("BButton::Draw() hook called");
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
	// GonxButton
	font_height fh;
	BRect r;
	_this->SetHighColor(_this->Parent()->ViewColor());
	_this->FillRect(_this->Bounds());
	if(_this->IsEnabled())
	{
		if(_this->Value())	
		{	
			r = _this->Bounds();
			_this->SetPenSize(1.0);
			BRect r2 = r;
			r2.left += 4;
			r2.right -= 4;
			r2.bottom -= 4;
			r2.top += 4;
			//Background
			//SetHighColor(Parent()->ViewColor());
			_this->SetHighColor(247,247,247); 
			_this->FillRect(r2);

			//shadow inside button
			_this->SetHighColor(223,223,218); 
			_this->StrokeLine(BPoint(r2.left,r2.top),BPoint(r2.right+1,r2.top)); //top shadow
			_this->SetHighColor(252,252,251); 
			_this->StrokeLine(BPoint(r2.right+1,r2.top),BPoint(r2.right+1,r2.bottom-1));//right and left shadow
			_this->StrokeLine(BPoint(r2.left-1,r2.top+1),BPoint(r2.left-1,r2.bottom));
			_this->SetHighColor(252,252,251); 
			_this->StrokeLine(BPoint(r2.left-1,r2.bottom),BPoint(r2.right,r2.bottom)); //bottom shadow

			
			//Top and bottom Outline
			_this->SetHighColor(140,140,121);
			_this->StrokeLine(BPoint(r2.left,r2.top-1),BPoint(r2.right+1,r2.top-1));
			_this->StrokeLine(BPoint(r2.left-1,r2.bottom+1),BPoint(r2.right,r2.bottom+1));

			//topleft and bottom right corners outline
			_this->StrokeLine(BPoint(r2.left,r2.top-1),BPoint(r2.left-2,r2.top+1));
			_this->StrokeLine(BPoint(r2.right,r2.bottom+1),BPoint(r2.right+2,r2.bottom-1));

			//left and right outline
			_this->StrokeLine(BPoint(r2.left-2,r2.top+2),BPoint(r2.left-2,r2.bottom));
			_this->StrokeLine(BPoint(r2.right+2,r2.top),BPoint(r2.right+2,r2.bottom-2));
			
			_this->SetDrawingMode(B_OP_ALPHA);

			//Shadow
			//Dark Shadow
			_this->SetHighColor(140,140,121,130);
			_this->StrokeLine(BPoint(r2.left,r2.bottom+2),BPoint(r2.right-1,r2.bottom+2)); //bottom shadow
			_this->StrokeLine(BPoint(r2.right,r2.bottom+2),BPoint(r2.right+3,r2.bottom-1)); //bottomright shadow
			_this->StrokeLine(BPoint(r2.right+3,r2.top+1),BPoint(r2.right+3,r2.bottom-2)); //rightside shadow

			_this->SetDrawingMode(B_OP_COPY);
			_this->SetHighColor(140,140,121);

		}
		else
		{
			r = _this->Bounds();
			_this->SetPenSize(1.0);
			BRect r2 = r;
			r2.left += 4;
			r2.right -= 4;
			r2.bottom -= 4;
			r2.top += 4;
			//Background
			//SetHighColor(Parent()->ViewColor());
			_this->SetHighColor(244,244,240); 
			_this->FillRect(r2);

			//shadow inside button
			_this->SetHighColor(252,252,251); 
			_this->StrokeLine(BPoint(r2.left,r2.top),BPoint(r2.right+1,r2.top)); //top shadow
			_this->SetHighColor(223,223,218); 
			_this->StrokeLine(BPoint(r2.right+1,r2.top),BPoint(r2.right+1,r2.bottom-1));//right and left shadow
			_this->StrokeLine(BPoint(r2.left-1,r2.top+1),BPoint(r2.left-1,r2.bottom));
			_this->SetHighColor(225,225,214); 
			_this->StrokeLine(BPoint(r2.left-1,r2.bottom),BPoint(r2.right,r2.bottom)); //bottom shadow

			
			//Top and bottom Outline
			_this->SetHighColor(140,140,121);
			_this->StrokeLine(BPoint(r2.left,r2.top-1),BPoint(r2.right+1,r2.top-1));
			_this->StrokeLine(BPoint(r2.left-1,r2.bottom+1),BPoint(r2.right,r2.bottom+1));

			//topleft and bottom right corners outline
			_this->StrokeLine(BPoint(r2.left,r2.top-1),BPoint(r2.left-2,r2.top+1));
			_this->StrokeLine(BPoint(r2.right,r2.bottom+1),BPoint(r2.right+2,r2.bottom-1));

			//left and right outline
			_this->StrokeLine(BPoint(r2.left-2,r2.top+2),BPoint(r2.left-2,r2.bottom));
			_this->StrokeLine(BPoint(r2.right+2,r2.top),BPoint(r2.right+2,r2.bottom-2));
			
			_this->SetDrawingMode(B_OP_ALPHA);

			//Shadow
			//Dark Shadow
			_this->SetHighColor(140,140,121,180);
			_this->StrokeLine(BPoint(r2.left,r2.bottom+2),BPoint(r2.right-1,r2.bottom+2)); //bottom shadow
			_this->StrokeLine(BPoint(r2.right,r2.bottom+2),BPoint(r2.right+3,r2.bottom-1)); //bottomright shadow
			_this->StrokeLine(BPoint(r2.right+3,r2.top+1),BPoint(r2.right+3,r2.bottom-2)); //rightside shadow

			//Light Shadow
			_this->SetHighColor(140,140,121,90);
			_this->StrokeLine(BPoint(r2.left+1,r2.bottom+3),BPoint(r2.right-1,r2.bottom+3)); //bottom shadow
			_this->StrokeLine(BPoint(r2.right,r2.bottom+3),BPoint(r2.right+3,r2.bottom)); //bottomright shadow
			_this->StrokeLine(BPoint(r2.right+4,r2.top+2),BPoint(r2.right+4,r2.bottom-1)); //rightside shadow

			_this->SetDrawingMode(B_OP_COPY);
			_this->SetHighColor(0,0,0);
		}
	}
	else
	{
		r = _this->Bounds();
		_this->SetPenSize(1.0);
		BRect r2 = r;
		r2.left += 4;
		r2.right -= 4;
		r2.bottom -= 4;
		r2.top += 4;
		//Background
		_this->SetHighColor(244,244,240); 
		_this->FillRect(r2);

		//shadow inside button
		_this->SetHighColor(252,252,251); 
		_this->StrokeLine(BPoint(r2.left,r2.top),BPoint(r2.right+1,r2.top)); //top shadow
		_this->SetHighColor(223,223,218); 
		_this->StrokeLine(BPoint(r2.right+1,r2.top),BPoint(r2.right+1,r2.bottom-1));//right and left shadow
		_this->StrokeLine(BPoint(r2.left-1,r2.top+1),BPoint(r2.left-1,r2.bottom));
		_this->SetHighColor(225,225,214); 
		_this->StrokeLine(BPoint(r2.left-1,r2.bottom),BPoint(r2.right,r2.bottom)); //bottom shadow

		
		//Top and bottom Outline
		_this->SetHighColor(140,140,121);
		_this->StrokeLine(BPoint(r2.left,r2.top-1),BPoint(r2.right+1,r2.top-1));
		_this->StrokeLine(BPoint(r2.left-1,r2.bottom+1),BPoint(r2.right,r2.bottom+1));

		//topleft and bottom right corners outline
		_this->StrokeLine(BPoint(r2.left,r2.top-1),BPoint(r2.left-2,r2.top+1));
		_this->StrokeLine(BPoint(r2.right,r2.bottom+1),BPoint(r2.right+2,r2.bottom-1));

		//left and right outline
		_this->StrokeLine(BPoint(r2.left-2,r2.top+2),BPoint(r2.left-2,r2.bottom));
		_this->StrokeLine(BPoint(r2.right+2,r2.top),BPoint(r2.right+2,r2.bottom-2));
		
		_this->SetDrawingMode(B_OP_ALPHA);

		//Shadow
		//Dark Shadow
		_this->SetHighColor(140,140,121,180);
		_this->StrokeLine(BPoint(r2.left,r2.bottom+2),BPoint(r2.right-1,r2.bottom+2)); //bottom shadow
		_this->StrokeLine(BPoint(r2.right,r2.bottom+2),BPoint(r2.right+3,r2.bottom-1)); //bottomright shadow
		_this->StrokeLine(BPoint(r2.right+3,r2.top+1),BPoint(r2.right+3,r2.bottom-2)); //rightside shadow

		//Light Shadow
		_this->SetHighColor(140,140,121,90);
		_this->StrokeLine(BPoint(r2.left+1,r2.bottom+3),BPoint(r2.right-1,r2.bottom+3)); //bottom shadow
		_this->StrokeLine(BPoint(r2.right,r2.bottom+3),BPoint(r2.right+3,r2.bottom)); //bottomright shadow
		_this->StrokeLine(BPoint(r2.right+4,r2.top+2),BPoint(r2.right+4,r2.bottom-1)); //rightside shadow

		_this->SetDrawingMode(B_OP_COPY);
		_this->SetHighColor(140,140,121);

	}

	be_plain_font->GetHeight(&fh);
	_this->MovePenTo((_this->Bounds().right/2)-((be_plain_font->StringWidth(_this->Label())/2)),(_this->Bounds().bottom/2)+(fh.ascent/2) - (!_this->Value()? 1:0));
	_this->DrawString(_this->Label());
//	if(BControl::IsFocus() && enabled) {
	if((_this->IsFocus() && _this->IsEnabled()) || _this->fDrawAsDefault) {
		rgb_color focusCol = ::ui_color(B_KEYBOARD_NAVIGATION_COLOR);
		if(!_this->IsFocus())
			focusCol = tint_color(focusCol, B_LIGHTEN_2_TINT);
//		_this->SetHighColor(80,114,154);
		_this->SetHighColor(focusCol);
		BPoint p1,p2;
		p1.x = (_this->Bounds().right/2)-((be_plain_font->StringWidth(_this->Label())/2))-1;
		p1.y = (_this->Bounds().bottom/2)+(fh.ascent/2)+1;
		p2.x =  p1.x + be_plain_font->StringWidth(_this->Label());
		p2.y = p1.y;
		_this->StrokeLine(p1,p2);
	}
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


}

#ifdef __cplusplus
}
#endif

