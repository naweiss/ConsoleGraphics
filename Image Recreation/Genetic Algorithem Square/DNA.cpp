#include "Square.cpp"

const int AMOUNT = 10;
const float MUTATION_RATE = 0.02;

class DNA{
public:
	Square* genes;

	DNA(){
		genes = new Square[AMOUNT];
	}
	
	DNA(Square* newgenes){
		genes = newgenes;
	}
	
	~DNA(){
		delete[] genes;
	}
	
	DNA* crossover(DNA* partner){
		Square* newgenes = new Square[AMOUNT];
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
				genes[i] = Square();
			}
		}
	}
	
	void show(){
		for (int i=0;i<AMOUNT;i++){
			genes[i].show();
		}
	}
};