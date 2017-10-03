#include "Pic.h"
#include <vector>
#include <fstream>
using namespace std;

extern const int POP_SIZE;
extern ofstream myfile;
extern double bestFitness;
extern Image* bestImg;

class Population{
private:
	Pic** pics;
	vector<Pic*> matingpool;
	
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