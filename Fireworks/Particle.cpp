#include "Particle.h"
#include "Maths.h"

Particle::Particle(float x, float y, COLORREF color, bool firework){
	this->firework = firework;
	this->color = color;
	pos = new Vector(x,y);
	if (firework){
		float ran = RandomF(8,13);
		vel = new Vector(0,-ran);
	} else {
		vel = new Vector(Vector::random2D());
		*vel *= RandomF(2,10);
	}
	acc = new Vector(0,0);
}

Particle::~Particle(){
	delete pos;
	delete vel;
	delete acc;
}

void Particle::applyForce(const Vector& force){
	*acc += force;
}

void Particle::update(){
	if (!firework){
		*vel *= 0.9;
	}
	*vel += *acc;
	*pos += *vel;
	*acc *= 0;
}

void Particle::show(){
	fill(color);
	drawCircle(pos->x,pos->y,3);
}