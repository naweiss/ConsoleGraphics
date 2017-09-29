#include "DNA.h"
#include "Maths.h"

DNA::DNA(float mutRate){
	this->mutRate = mutRate;
	for (int i=0;i<lifespan;i++){
		genes.push_back(Vector::random2D()/5);
	}
}

// DNA::DNA(const DNA& obj){
	// for (int i=0;i<lifespan;i++){
		// genes.push_back(new Vector(*(obj.genes[i])));
	// }
	// this->mutRate = obj.mutRate;
// }

// DNA::~DNA(){
	// for (int i=0;i<lifespan;i++){
		// delete genes[i];
	// }
// }

DNA::DNA(vector<Vector> newgenes,float mutRate){
	for (int i=0;i<lifespan;i++){
		genes.push_back(newgenes[i]);
	}
	this->mutRate = mutRate;
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
	return DNA(newgenes,mutRate);
}

void DNA::mutations(){
	for (int i=0;i<lifespan;i++){
		if (RandomF(1) < mutRate){
			// delete genes[i];
			genes[i] = Vector::random2D()/5;
		}
	}
}