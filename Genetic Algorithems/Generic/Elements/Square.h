#ifndef GRAPHICS
#include "Graphics.h"
#define GRAPHICS
#endif // !GRAPHICS
#ifndef VECTOR
#include "Vector.h"
#define VECTOR
#endif // !VECTOR
#ifndef ELEMENT
#include "Element.h"
#define ELEMENT
#endif // !ELEMENT

class Square : public Element{
	void init();
public:
	Vector p;
	int w;
	int h;
	COLORREF color;
	
	Square();
	
	Square(Vector p, int w, int h, COLORREF color);
		
	void show(int x_offset, int y_offset);
	
	void mutate();
};