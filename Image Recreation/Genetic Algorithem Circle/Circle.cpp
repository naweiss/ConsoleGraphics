#include "Circle.h"
#include "Maths.h"

Image* img;

Circle::Circle(){
	p = Vector(Random(img->width),Random(img->height));
	r = Random(min(img->width/4,img->height/4));
	int num = Random(256);
	color = RGB(num,num,num);
}

Circle::Circle(Vector p, int r, COLORREF color){
	this->p = p;
	this->r = r;
	this->color = color;
}
	
void Circle::show(){
	fill(color);
	drawCircle(p.x,p.y,r);
}