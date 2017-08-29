#include "DNA.h"

extern int n;
const short rx = 200;
const short ry = 150;
const short rw = 300;
const short rh = 10;
extern Vector target;

class Rocket{
public:
	Vector pos;
	Vector vel;
	Vector acc;
	DNA dna;
	double fitness;
	bool completed;
	bool crashed;
	
	Rocket();
	
	void applyForce(Vector force);
	
	void calaFitness();
	
	void update();
	
	void show();
};