#include "Graphics.h"
#include "Rocket.h"
#include <iostream>
using namespace std;

int n = 0;
Vector target;

Rocket::Rocket(float mutRate){
	this->mutRate = mutRate;
	dna = DNA(mutRate);
	completed = false;
	crashed = false;
	pos = Vector(width/4,height/2);
	vel = Vector();
	acc = Vector();
	fitness = 0;
}

void Rocket::applyForce(Vector force){
	this->acc += force;
}

void Rocket::calaFitness(){
	double d = pos.dist(target);
	fitness = ((width/2) - d)/(width/2);
	if (completed)
		fitness *= 10;
	if (crashed)
		fitness /= 10;
}

void Rocket::update(){
	if (pos.dist(target) < 10){
		completed = true;
		pos = target;
	}
	if (pos.x > rx && pos.x < rx + rw && pos.y > ry && pos.y < ry + rh) {
	  crashed = true;
	}

	if (pos.x > width/2 || pos.x < 0) {
	  crashed = true;
	}
	if (pos.y > height/2 || pos.y < 0) {
	  crashed = true;
	}
	if (!completed && !crashed){
		applyForce(dna.genes[n]);
		
		this->vel += acc;
		this->vel.limit(4);
		this->pos += vel;
		this->acc *= 0;
	}
}

void Rocket::show(){
	Vector end = pos-(vel/vel.mag())*15;
	drawLine(pos.x,pos.y,end.x,end.y);
}