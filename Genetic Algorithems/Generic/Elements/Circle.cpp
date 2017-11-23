#include "Circle.h"
#include "Maths.h"

void Circle::init()
{
	p = Vector(Random(originalImg->width), Random(originalImg->height));
	r = Random(1, 15);
	int num = 255;//Random(256);
	color = RGB(num, num, num);
}

Circle::Circle(){
	this->init();
}
	
void Circle::show(int x_offset, int y_offset){
	fill(color);
	drawCircle(p.x + x_offset, p.y + y_offset, r);
}

void Circle::mutate()
{
	this->init();
}
