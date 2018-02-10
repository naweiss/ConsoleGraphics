#include "Graphics.h"
#include "Maths.h"

static Image* img = NULL;
void setup(){
	img = loadImage("frog.bmp");
	createCanvas(img->width,img->height);
	noStroke();
}

void draw(){
	alpha(30);
	for (int i = 0; i < 500; i++){
		int x = Random(width);
		int y = Random(height);
		COLORREF c = img->get(x,y);
		fill(c);
		drawCircle(x,y,4);
	}
}