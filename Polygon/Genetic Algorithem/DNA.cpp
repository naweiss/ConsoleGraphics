#include "Triangle.cpp"

const int AMOUNT = 10;
const float MUTATION_RATE = 0.02;

class DNA{
public:
	Triangle* genes;

	DNA(){
		genes = new Triangle[AMOUNT];
	}
	
	DNA(Triangle* newgenes){
		genes = newgenes;
	}
	
	~DNA(){
		delete[] genes;
	}
	
	DNA* crossover(DNA* partner){
		return new DNA();
		Triangle* newgenes = new Triangle[AMOUNT];
		int mid = AMOUNT/2;
		for (int i=0;i<AMOUNT;i++){
			if (i > mid){
				newgenes[i] = genes[i];
			} else {
				newgenes[i] = partner->genes[i];
			}
		}
		return new DNA(newgenes);
	}
	
	void mutation(){
		for (int i=0;i<AMOUNT;i++){
			if (RandomF(1) < MUTATION_RATE){
				genes[i] = Triangle();
			}
		}
	}
	
	void show(){
		for (int i=0;i<AMOUNT;i++){
			genes[i].show();
		}
	}
};