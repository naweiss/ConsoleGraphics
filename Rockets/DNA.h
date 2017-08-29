#include "Vector.h"
#include <vector>

const int lifespan = 400;

class DNA{
public:
	vector<Vector> genes;
	
	DNA();
	
	DNA(vector<Vector> newgenes);
	
	DNA crossover(DNA partner);
	
	void mutations();
};