#include "Graphics.cpp"
#include "Math.cpp"

static Image* img = NULL;
void setup(){
	img = loadImage("frog2.bmp");
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