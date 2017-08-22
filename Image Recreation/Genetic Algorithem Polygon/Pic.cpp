#include "DNA.cpp"
#include <vector>

class Pic{
public:
	DNA* dna;
	double fitness;
	
	Pic(){
		dna = new DNA;
		fitness = 0;
	}
	
	Pic(DNA* new_dna){
		fitness = 0;
		dna = new_dna;
	}
	
	~Pic(){
		delete dna;
	}
	
	void calaFitness(){
		fitness = 1-dna->calaFitness();
	}
	
	void show(){
		background();
		dna->show();
	}
};