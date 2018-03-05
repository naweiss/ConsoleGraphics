#include "CharImage.h"
#include <time.h>
#define TEXT_SIZE 10

CharImage* ascii_img;

clock_t t0;
double msPassed(){
	clock_t t1 = clock();
    double diffms=(t1-t0)/(CLOCKS_PER_SEC/1000);
	t0 = t1;
    return diffms;
}

void setup(){
	Image* img = loadImage("test.bmp");
	createCanvas(img->width,img->height);
	fill(RGB(0,0,0));
	textSize(TEXT_SIZE);
	noStroke();
	t0 = clock();
	ascii_img = new CharImage(img);
	cout << "Init:" << endl;
	cout << msPassed()/1000 << endl;
}

void draw(){
	t0 = clock();
	while(!ascii_img->finished())
		ascii_img->nextChar();
	cout << "Creating Image:" << endl;
	cout << msPassed()/1000 << endl;
	ascii_img->draw();
	SaveBMP(GetCanvas(),"ans.bmp");
	delete ascii_img;
	noLoop();
}