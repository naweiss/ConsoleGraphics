#include "Firework.h"
#include "Maths.h"

Vector* Firework::gravity = new Vector(0,0.2);

Firework::Firework(COLORREF color){
	firework = new Particle(Random(width),height,color);
	this->lifespan = 150;
	this->color = color;
}

Firework::~Firework(){
	if (firework != NULL)
		delete firework;
	for (vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it){
		delete *it;
	}
	particles.clear();
}

bool Firework::dead(){
	return ((firework == NULL) && (particles.size() == 0));
}

void Firework::expload(){
	for (int i = 0; i < 80; i++){
		particles.push_back(new Particle(firework->pos->x, firework->pos->y,color , false));
	}
}

void Firework::update(){
	if (firework != NULL){
		firework->applyForce(*gravity);
		firework->update();
		if (firework->vel->y >= 0){
			expload();
			delete firework;
			firework = NULL;
		}
	} else if (lifespan > 0){
		lifespan-=4;
		for (vector<Particle*>::iterator it = particles.begin() ; it != particles.end();){
			(*it)->applyForce(*gravity);
			(*it)->update();
			++it;
		}
	} else {
		particles.clear();
	}
}

bool Firework::done(){
	return (lifespan < 0);
}

void Firework::show(){
	if (firework != NULL){
		firework->show();
	}else{
		for (int i = 0; i < particles.size(); i++){
			particles[i]->show();
		}
	}
}