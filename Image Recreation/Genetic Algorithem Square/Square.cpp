#include "Square.h"
#include "Maths.h"

Image* img;

Square::Square(){
	p = Vector::random2D()*RandomF(img->width);
	w = Random(img->width);
	h = Random(img->height);
	if (p.x < 0)
		p.x = 0;
	if (p.y < 0)
		p.y = 0;
	if (w+p.x > img->width)
		w = img->width-p.x;
	if (h+p.y > img->height)
		h = img->height-p.y;
	int num = Random(2) == 1 ? 255 : 0;
	color = RGB(num,num,num);
}

Square::Square(Vector p, int w, int h, COLORREF color){
	this->p = p;
	this->w = w;
	this->h = h;
	this->color = color;
}
	
void Square::show(){
	fill(color);
	drawRectangle(p.x,p.y,w,h);
}