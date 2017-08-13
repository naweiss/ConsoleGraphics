#include "Graphics.cpp"
#include "Vector.cpp"

class Square{
public:
	Vector p;
	int w;
	int h;
	COLORREF color;
	
	Square(){
		p = Vector::random2D()*RandomF(width);
		w = h = 10;
		int num = Random(2) == 1 ? 255 : 0;
		color = RGB(num,num,num);
	}
	
	Square(Vector p, int w, int h, COLORREF color){
		this->p = p;
		this->w = w;
		this->h = h;
		this->color = color;
	}
		
	void show(){
		fill(color);
		drawRectangle(p.x,p.y,w,h);
	}
};