#include <stdio.h>
#include <OS.h>
#include <View.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int32 BApp_created;

void hooked_Draw__5BViewG5BRect(BView *_this, BRect updateRect)
{
	puts("BView::Draw() hook called");
	_this->PushState();
	_this->StrokeRect(updateRect);
	_this->PopState();
}

#ifdef __cplusplus
}
#endif

