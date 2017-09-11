#include "Graphics.h"

class Particle{
public:
	float x;
	float y;

	float vx;
	float vy;
	Image* frog;

	Particle() {}
	
	Particle(Image* frog);
	
	void display();
	
	void move();
};