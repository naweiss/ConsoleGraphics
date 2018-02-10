#include "Graphics.h"

COLORREF color_gray_scale(COLORREF color){
	//Gray-Scale color: 0.21 R + 0.72 G + 0.07 B.
	short bright= GetRValue(color)*0.21+GetGValue(color)*0.72+GetBValue(color)*0.07;
	return RGB(bright,bright,bright);
}

void image_gray_scale(Image* image){
	for(int i=0;i<image->width;i++)
		for(int j=0;j<image->height;j++)
			image->set(i,j,color_gray_scale(image->get(i,j)));
}

Image* img;

void setup(){
	img = loadImage("img2.bmp");
	image_gray_scale(img);
}

void draw(){
	drawImage(img);
	noLoop();
}