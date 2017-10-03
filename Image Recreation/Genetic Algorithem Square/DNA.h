#include "Square.h"

class DNA{
public:
	Square* genes;

	DNA();
	
	DNA(Square* newgenes);
	
	~DNA();
	
	DNA* crossover(DNA* partner);
	
	double calaFitness();
	
	void mutation();
	
	void show();
};