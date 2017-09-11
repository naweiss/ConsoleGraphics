#include "Graphics.h"
#include "Maths.h"

static Image* img = NULL;
void setup(){
	img = loadImage("frog.bmp");
	width = img->width;
	height = img->height;
	background();
}

void draw(){
	alpha(15);
	for (int i = 0; i < 500; i++){
		int x = Random(width);
		int y = Random(height);
		COLORREF c = img->get(x,y);
		fill(c);
		drawEllipse(x,y,4,4);
	}
}