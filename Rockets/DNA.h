#include "Vector.h"
#include <vector>

const int lifespan = 400;

class DNA{
	float mutRate;
public:
	vector<Vector> genes;
	
	DNA(float mutRate = 0);
	DNA(vector<Vector> newgenes, float mutRate);
	// DNA(const DNA& obj);
	// ~DNA();
		
	DNA crossover(DNA partner);
	void mutations();
};