#include "Graphics.cpp"
#include "Math.cpp"

class Particle{
public:
	float x;
	float y;

	float vx;
	float vy;
	Image* frog;

	Particle() {}
	
	Particle(Image* frog) {
		this->frog = frog;
		x = width/2;
		y = height/2;
		float a = Random(PI*2*1000);
		float speed = Random(1000,4000)/10000.0;
		vx = cos(a/1000.0)*speed;
		vy = sin(a/1000.0)*speed;
	}
	
	void display() {
		COLORREF c = frog->pixels[((int)x)+((int)y)*width];
		fill(c);
		drawEllipse(x, y, 3, 3);
	}
	
	void move() {
		x = x + vx;//random(-5, 5);
		y = y + vy;//random(-5, 5);
		if (y < 0) {
			y = height;
		} 
		if (y > height) {
			y = 0;
		}
		if (x < 0) {
			x = width;
		} 
		if (x > width) {
			x = 0;
		}
	}
};