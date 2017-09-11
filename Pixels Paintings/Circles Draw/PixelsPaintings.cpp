#include "Graphics.h"
#include "Maths.h"

static Image* img = NULL;
void setup(){
	img = loadImage("frog.bmp");
	width = img->width;
	height = img->height;
	background();
	noStroke();
}

void draw(){
	int x = Random(width);
	int y = Random(height);
	COLORREF c = img->get(x,y);
	fill(c);
	drawEllipse(x,y,4,4);
}