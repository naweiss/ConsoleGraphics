#include "Graphics.h"
#include "Vector.h"

extern Image* img;

class Square{
public:
	Vector p;
	int w;
	int h;
	COLORREF color;
	
	Square();
	
	Square(Vector p, int w, int h, COLORREF color);
		
	void show();
};