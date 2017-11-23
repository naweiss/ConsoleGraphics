#include "DNA.h"
#include <vector>
#include <fstream>

class Population{
private:
	int id;
	float mutRate;
	DNA** dnas;
	vector<DNA*> matingpool;
	
	void free();
public:
	double bestFitness;
	double maxFitness;
	double avgFitness;
	Image* bestImg;
	int size;
	
	Population(int id, int size, int amount, ElementType type, float mutRate);
	
	~Population();
	
	void evaluate(short index);
	
	void evaluate();
	
	void selection();
	
	void run(short index);

	void saveBest(const char* path, const char* file_name, const char* type);
};