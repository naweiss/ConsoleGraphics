#include "Graphics.h"
#include "Vector.h"
#include "Element.h"

extern Image* img;

class Square : public Element{
	void init();
public:
	Vector p;
	int w;
	int h;
	COLORREF color;
	
	Square();
	
	Square(Vector p, int w, int h, COLORREF color);
		
	void show();
	
	void mutate();
};