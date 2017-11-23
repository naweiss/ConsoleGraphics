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

class Circle : public Element {
	void init();
public:
	Vector p;
	int r;
	COLORREF color;
	
	Circle();
		
	void show(int x_offset, int y_offset);

	void mutate();
};