#include "Graphics.h"
#include "Contrast.h"
#include <iostream>
using namespace std;

Image* img;
const int contrast = 128; // in range [-255,255];

void setup(){
	img = loadImage("test.bmp");
	createCanvas(img->width, img->height);
	image_contrast(img,contrast);
	SaveBMP(img,"ans.bmp");
}

void draw(){
	drawImage(img);
	noLoop();
}