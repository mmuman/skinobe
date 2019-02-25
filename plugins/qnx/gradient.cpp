#include <stdio.h>
#include <View.h>
#include "gradient.h"

void draw_qnx_gradiant(BView *view, BRect frame, bool raised, rgb_color color1, rgb_color color2, bool vertical)
{
	int i, numlines;
	float fI, fNumlines;
	BPoint a, b;
	rgb_color line_color;
	rgb_color oldHighcolor = view->HighColor();

fprintf(stderr, "draw_qnx_gradiant(%p, (%f, %f, %f, %f), %s, , , %s)\n", view, frame.left, frame.top, frame.right, frame.bottom, raised?"true":"false", vertical?"true":"false");

	line_color.alpha = 255;

	if (vertical) {
		a.x = frame.left;
		b.x = frame.right;
		a.y = b.y = frame.top;
	} else {
		a.y = frame.top;
		b.y = frame.bottom;
		a.x = b.x = frame.left;
	}

	numlines = (int)(vertical?frame.Height():frame.Width()) + 1;

	if (numlines < 1)
		return;

	view->PushState();
fprintf(stderr, "numlines = %d\n", numlines);

	if (numlines <= 128) { // LineArray method
fprintf(stderr, "LineArray method\n");
		fNumlines = numlines;

		view->BeginLineArray(numlines);
		for (i = 0; i < numlines; i++) {
			fI = raised?i:(numlines-i);
			line_color.red =   (uchar)( (((float)color1.red)   * (fNumlines - fI) + ((float)color2.red)   * fI ) / (fNumlines) );
			line_color.green = (uchar)( (((float)color1.green) * (fNumlines - fI) + ((float)color2.green) * fI ) / (fNumlines) );
			line_color.blue =  (uchar)( (((float)color1.blue)  * (fNumlines - fI) + ((float)color2.blue)  * fI ) / (fNumlines) );
			// might produce interesting effects =)
			//line_color.alpha = (uint8)(((((numlines - i) / numlines) *(float)color1.alpha) + ((i/numlines) * (float)color2.alpha)) / 2);

			view->AddLine(a, b, line_color);

			if (vertical) { a.y++; b.y++; }
			else { a.x++; b.x++; }
		}
		view->EndLineArray();
	} else { // too many lines, use Recangles
fprintf(stderr, "Recangles method\n");
		numlines = MIN(128, numlines / 2);
		fNumlines = numlines;
		if (vertical)
			b.y += (i * frame.Height()) / numlines;
		else
			b.x += (i * frame.Width()) / numlines;
		for (i = 0; i < numlines; i++) {
			fI = raised?i:(numlines-i);
			line_color.red =   (uchar)( (((float)color1.red)   * (fNumlines - fI) + ((float)color2.red)   * fI ) / (fNumlines) );
			line_color.green = (uchar)( (((float)color1.green) * (fNumlines - fI) + ((float)color2.green) * fI ) / (fNumlines) );
			line_color.blue =  (uchar)( (((float)color1.blue)  * (fNumlines - fI) + ((float)color2.blue)  * fI ) / (fNumlines) );
			view->SetHighColor(line_color);
			view->FillRect(BRect(a, b));
			if (vertical) {
				a.y = frame.top + (i * frame.Height()) / numlines;
				b.y = frame.top + ((i + 1) * frame.Height()) / numlines;
			} else {
				a.x = frame.left + (i * frame.Width()) / numlines;
				b.x = frame.left + ((i + 1) * frame.Width()) / numlines;
			}
		}
	}

	view->PopState();
	view->SetHighColor(oldHighcolor); // ??
}

