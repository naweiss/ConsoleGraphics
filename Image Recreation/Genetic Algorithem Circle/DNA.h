#include "Circle.h"

class DNA{
public:
	Circle* genes;

	DNA();
	
	DNA(Circle* newgenes);
	
	~DNA();
	
	DNA* crossover(DNA* partner);
	
	double calaFitness();
	
	void mutation();
	
	void show();
};