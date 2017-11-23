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

class Triangle : public Element {
	void init();
	
	float sign(Vector p1, Vector p2, Vector p3);

	bool inside_triangle(Vector pt);
	
	void calcBorder(Vector p);
public:
	Vector p1;
	Vector p2;
	Vector p3;
	int l,r,t,b;
	COLORREF color;
	
	Triangle();
		
	void show(int x_offset, int y_offset);

	void mutate();
};