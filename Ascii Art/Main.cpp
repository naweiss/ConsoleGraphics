#include "CharImage.h"
#define TEXT_SIZE 10

CharImage* ascii_img;

void setup(){
	Image* img = loadImage("test.bmp");
	createCanvas(img->width,img->height);
	fill(RGB(0,0,0));
	textSize(TEXT_SIZE);
	noStroke();
	ascii_img = new CharImage(img);
}

void draw(){
	while(!ascii_img->finished())
		ascii_img->nextChar();
	ascii_img->draw();
	SaveBMP(GetCanvas(),"ans.bmp");
	delete ascii_img;
	noLoop();
}