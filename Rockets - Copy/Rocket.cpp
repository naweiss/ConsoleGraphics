#include "Graphics.cpp"
#include "DNA.cpp"

int n = 0;
short rx = 200;
short ry = 150;
short rw = 300;
short rh = 10;
Vector target;

class Rocket{
public:
	Vector pos;
	Vector vel;
	Vector acc;
	DNA dna;
	double fitness;
	bool completed;
	bool crashed;
	
	Rocket(){
		completed = false;
		crashed = false;
		pos = Vector(width/2,height);
		vel = Vector();
		acc = Vector();
		fitness = 0;
	}
	
	void applyForce(Vector force){
		this->acc += force;
	}
	
	void calaFitness(){
		double d = pos.dist(target);
		fitness = (width - d)/width;
		if (completed)
			fitness *= 10;
		if (crashed)
			fitness /= 10;
	}
	
	void update(){
		if (pos.dist(target) < 10){
			completed = true;
			pos = target;
		}
		if (pos.x > rx && pos.x < rx + rw && pos.y > ry && pos.y < ry + rh) {
		  crashed = true;
		}

		if (pos.x > width || pos.x < 0) {
		  crashed = true;
		}
		if (pos.y > height || pos.y < 0) {
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
	
	void show(){
		Vector end = pos-(vel/vel.mag())*15;
		drawLine(pos.x,pos.y,end.x,end.y);
	}
};