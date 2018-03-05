#include "Graphics.h"
#include "Contrast.h"

int Truncate(int value){
	if(value < 0)
		return 0;
	if(value > 255)
		return 255;
	return value;
}

COLORREF apply_contrast(COLORREF color, int contrast){
	float factor = (259 * (contrast + 255));
	factor /= (255 * (259 - contrast));
	int r = Truncate(factor * (GetRValue(color) - 128) + 128);
	int g = Truncate(factor * (GetGValue(color) - 128) + 128);
	int b = Truncate(factor * (GetBValue(color) - 128) + 128);
	return RGB(r, g, b);
}

void image_contrast(Image* image, int contrast){
	if(contrast > 255 || contrast < -255)
		return;
	for(int i=0;i<image->width;i++)
		for(int j=0;j<image->height;j++)
			image->set(i,j,apply_contrast(image->get(i,j), contrast));
}