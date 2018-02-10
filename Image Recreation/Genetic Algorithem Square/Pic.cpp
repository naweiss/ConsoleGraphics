#include "Pic.h"

Pic::Pic(){
	dna = new DNA;
	fitness = 0;
}

Pic::Pic(DNA* new_dna){
	fitness = 0;
	dna = new_dna;
}

Pic::~Pic(){
	delete dna;
}

void Pic::calaFitness(){
	fitness = 1-dna->calaFitness();
}

void Pic::show(){
	background();
	dna->show();
}