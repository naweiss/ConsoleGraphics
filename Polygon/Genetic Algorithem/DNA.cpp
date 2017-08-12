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
	
	DNA(const DNA &obj) {
		genes = new Triangle[AMOUNT];
		for (int i=0;i<AMOUNT;i++){
			genes[i] = obj.genes[i];
		}
	}
	
	const DNA &operator=(const DNA &other)
	{
		if(this == &other) return *this; // handling of self assignment, thanks for your advice, arul.
		delete[] genes; // freeing previously used memory
		genes = new Triangle[AMOUNT];
		for (int i=0;i<AMOUNT;i++){
			genes[i] = obj.genes[i];
		}
		return *this;
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