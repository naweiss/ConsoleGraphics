#include "Graphics.cpp"
#include "Math.cpp"

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
		int index = x+y*width;
		COLORREF c = img->pixels[index];
		fill(c);
		drawEllipse(x,y,4,4);
	}
}