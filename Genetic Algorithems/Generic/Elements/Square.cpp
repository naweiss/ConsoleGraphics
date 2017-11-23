#include "Square.h"
#include "Maths.h"

void Square::init(){
	color = RGB(255, 255, 255);
	w = Random(originalImg->width/2);
	h = Random(originalImg->height/2);
	p = Vector(Random(originalImg->width - w), Random(originalImg->height - h));
}

Square::Square(){
	this->init();
}

Square::Square(Vector p, int w, int h, COLORREF color){
	this->p = p;
	this->w = w;
	this->h = h;
	this->color = color;
}
	
void Square::show(int x_offset, int y_offset){
	fill(color);
	drawRectangle(p.x + x_offset, p.y + y_offset, w, h);
}

void Square::mutate(){
	this->init();
}