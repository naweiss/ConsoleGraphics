#include "Particle.h"
#include <ctime>

static Image* frog;
static Particle** particles;
static long length;

void setup(){
	srand(time(NULL));
	frog = loadImage("frog.bmp");
	createCanvas(frog->width,frog->height);
	noStroke();
	
	length = 70;
	particles = new Particle*[length];
	for (int i = 0; i < length; i++) {
		particles[i] = new Particle(frog);
	}
	background();
}

void draw(){
	for (int i = 0; i < length; i++) {
		particles[i]->display();
		particles[i]->move();
	}
}
