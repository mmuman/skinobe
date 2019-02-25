#include <View.h>

#ifndef _QNX_GRADIENT_H
#define _QNX_GRADIENT_H

//const rgb_color GRADIENT_DEFAULT_COLOR1 = {227, 227, 227, 255};
//const rgb_color GRADIENT_DEFAULT_COLOR2 = {169, 169, 169, 255};
const rgb_color GRADIENT_DEFAULT_COLOR1 = {236, 236, 236, 255};
const rgb_color GRADIENT_DEFAULT_COLOR2 = {196, 196, 196, 255};

extern void draw_qnx_gradiant(BView *view, BRect frame,
				bool raised = true, // false inverts the 2 colors
				rgb_color color1 = GRADIENT_DEFAULT_COLOR1,
				rgb_color color2 = GRADIENT_DEFAULT_COLOR2,
				bool vertical = true); // top-bottom, else from left to right (or reversed if raised = false)

#endif /* _QNX_GRADIENT_H */

