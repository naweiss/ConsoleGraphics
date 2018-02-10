#include "Triangle.h"

class DNA{
public:
	Triangle* genes;
	Image* my_img;

	DNA();
	
	DNA(Triangle* newgenes);
	
	~DNA();
	
	DNA* crossover(DNA* partner);
	
	double calaFitness();
	
	void mutation();
	
	void show();
};