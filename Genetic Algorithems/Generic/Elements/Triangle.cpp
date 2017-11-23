#include "Triangle.h"
#include "Maths.h"

Triangle::Triangle(){
	this->init();
}

void Triangle::init()
{
	color = RGB(255, 255, 255);
	r = originalImg->width;
	b = originalImg->height;
	l = t = 0;
	p1 = Vector(Random(r), Random(b));
	p2 = Vector::random2D()*Random(max(r, b)) + p1;
	p3 = Vector::random2D()*Random(max(r, b)) + p1;
	calcBorder(p1);
	calcBorder(p2);
	calcBorder(p3);
}

float Triangle::sign(Vector p1, Vector p2, Vector p3){
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool Triangle::inside_triangle(Vector pt){
	bool b1, b2, b3;

	b1 = sign(pt, p1, p2) < 0.0f;
	b2 = sign(pt, p2, p3) < 0.0f;
	b3 = sign(pt, p3, p1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

void Triangle::calcBorder(Vector p){
	if (p.x < r && p.x > 0)
		r = p.x;
	if (p.y < b && p.y > 0)
		b = p.y;
	if (p.x > l && p.x < originalImg->width)
		l = p.x;
	if (p.y > t && p.y < originalImg->height)
		t = p.y;
}

void Triangle::show(int x_offset, int y_offset){
	for (int i = r;i < l;i++){
		for (int j = b;j < t;j++){
			if (inside_triangle(Vector(i,j))){
				fill(this->color);
				SetPixelC(i + x_offset, j + y_offset);
			}
		}
	}
}

void Triangle::mutate() {
	this->init();
}