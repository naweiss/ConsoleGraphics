#include "DNA.h"
#include <fstream>

extern const int POP_SIZE;
extern ofstream myfile;
extern double bestFitness;
extern Image* bestImg;

class Population{
private:
	DNA** pics;
	vector<DNA*> matingpool;
	
	void free();
public:
	int generation;
	
	Population();
	
	~Population();
	
	void evaluate(short index);
	
	void evaluate();
	
	void selection();
	
	void run(short index);
};