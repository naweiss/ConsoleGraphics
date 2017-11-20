#include "Pic.h"
#include <vector>
#include <fstream>
using namespace std;

class Population{
private:
	short id;
	float mutRate;
	ofstream log;
	Pic** pics;
	vector<Pic*> matingpool;
	
	void free();
public:
	Image* bestImg;
	static const int POP_SIZE;
	double bestFitness;
	int generation;
	
	Population(short id, float mutRate);
	
	~Population();
	
	void evaluate(short index);
	
	void evaluate();
	
	void selection();
	
	void run(short index);
};