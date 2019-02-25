#include <stdio.h>
#include <OS.h>
#include <View.h>

#include "osxstipple.h"

#ifdef __cplusplus
extern "C" {
#endif

void BView__Draw(BView *_this, BRect updateRect)
{
	/*if (!_this->Window())
		return;*/
	puts("BView::Draw() hook called");
	_this->PushState();
	draw_osx_stipple(_this, updateRect);
	//_this->StrokeRect(updateRect);
	_this->PopState();
}

#ifdef __cplusplus
}
#endif

