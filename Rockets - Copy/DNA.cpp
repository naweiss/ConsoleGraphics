#include "Vector.cpp"
#include <vector>

int lifespan = 400;

class DNA{
public:
	vector<Vector> genes;
	DNA(){
		for (int i=0;i<lifespan;i++){
			genes.push_back(Vector::random2D()/5);
		}
	}
	
	DNA(vector<Vector> newgenes){
		genes = newgenes;
	}
	
	DNA crossover(DNA partner){
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
	
	void mutations(){
		for (int i=0;i<lifespan;i++){
			if (RandomF(1) < 0.01){
				genes[i] = Vector::random2D()/5;
			}
		}
	}
};