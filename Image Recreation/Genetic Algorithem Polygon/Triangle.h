#include "Graphics.h"
#include "Vector.h"

extern Image* img;

class Triangle{
public:
	Vector p1;
	Vector p2;
	Vector p3;
	int l,r,t,b;
	COLORREF color;
	
	Triangle();
	
	Triangle(Vector p1, Vector p2, Vector p3, COLORREF color);
	
	float sign(Vector p1, Vector p2, Vector p3);

	bool inside_triangle(Vector pt);
	
	void calcBorders(Vector p);
	
	void show(Image* my_img);
};