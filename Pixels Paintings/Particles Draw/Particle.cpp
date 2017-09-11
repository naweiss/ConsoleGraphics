#include "Particle.h"
#include "Maths.h"
#include <cmath>

Particle::Particle(Image* frog) {
	this->frog = frog;
	x = width/2;
	y = height/2;
	float a = Random(PI*2*1000);
	float speed = Random(1000,4000)/10000.0;
	vx = cos(a/1000.0)*speed;
	vy = sin(a/1000.0)*speed;
}

void Particle::display() {
	COLORREF c = frog->get((int)x,(int)y);
	fill(c);
	drawEllipse(x, y, 3, 3);
}

void Particle::move() {
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