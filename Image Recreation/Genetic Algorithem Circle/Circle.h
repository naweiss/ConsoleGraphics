#include "Graphics.h"
#include "Vector.h"

extern Image* img;

class Circle{
public:
	Vector p;
	int r;
	COLORREF color;
	
	Circle();
	
	Circle(Vector p, int r, COLORREF color);
		
	void show();
};