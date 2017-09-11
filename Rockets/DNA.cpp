#include "DNA.h"
#include "Maths.h"

DNA::DNA(){
	for (int i=0;i<lifespan;i++){
		genes.push_back(Vector::random2D()/5);
	}
}

DNA::DNA(vector<Vector> newgenes){
	genes = newgenes;
}

DNA DNA::crossover(DNA partner){
	vector<Vector> newgenes;
	int mid = Random(lifespan);
	for (int i=0;i<lifespan;i++){
		if (i > mid){
			newgenes.push_back(genes[i]);
		} else {
			newgenes.push_back(partner.genes[i]);
		}
	}
	return DNA(newgenes);
}

void DNA::mutations(){
	for (int i=0;i<lifespan;i++){
		if (RandomF(1) < 0.01){
			genes[i] = Vector::random2D()/5;
		}
	}
}