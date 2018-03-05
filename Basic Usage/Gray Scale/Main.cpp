#include "GrayScale.h"
#include "Graphics.h"

Image* img;

void setup(){
	img = loadImage("test.bmp");
	createCanvas(img->width, img->height);
	image_gray_scale(img);
	SaveBMP(img,"ans.bmp");
}

void draw(){
	drawImage(img);
	noLoop();
}