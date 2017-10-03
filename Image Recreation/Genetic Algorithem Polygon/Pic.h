#include "DNA.h"

class Pic{
public:
	DNA* dna;
	double fitness;
	
	Pic();
	
	Pic(DNA* new_dna);
	
	~Pic();
	
	void calaFitness();
	
	void show();
};