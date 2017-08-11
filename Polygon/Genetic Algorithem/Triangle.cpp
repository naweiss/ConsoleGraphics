#include "Graphics.cpp"
#include "Vector.cpp"

class Triangle{
public:
	Vector p1;
	Vector p2;
	Vector p3;
	int l,r,t,b;
	COLORREF color;
	
	Triangle(){
		r = b = width;
		l = t = 0;
		p1 = Vector::random2D()*RandomF(width/2)+Vector(width/2,width/2);
		p2 = Vector::random2D()*RandomF(width)+p1;
		p3 = Vector::random2D()*RandomF(width)+p1;
		color = RGB(Random(256),Random(256),Random(256));
		calcBorders(p1);
		calcBorders(p2);
		calcBorders(p3);
	}
	
	Triangle(Vector p1, Vector p2, Vector p3, COLORREF color){
		r = b = width;
		l = t = 0;
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		this->color = color;
		calcBorders(p1);
		calcBorders(p2);
		calcBorders(p3);
	}
	
	float sign(Vector p1, Vector p2, Vector p3){
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

	bool inside_triangle(Vector pt){
		bool b1, b2, b3;

		b1 = sign(pt, p1, p2) < 0.0f;
		b2 = sign(pt, p2, p3) < 0.0f;
		b3 = sign(pt, p3, p1) < 0.0f;

		return ((b1 == b2) && (b2 == b3));
	}
	
	void calcBorders(Vector p){
		if (p.x < r)
			r = p.x;
		if (p.y < b)
			b = p.y;
		if (p.x > l)
			l = p.x;
		if (p.y > t)
			t = p.y;
	}
	
	void show(){
		fill(color);
		for (int i = r;i < l;i++){
			for (int j = b;j < t;j++){
				if (inside_triangle(Vector(i,j))){
					SetPixelC(i,j);
				}
			}
		}
	}
};