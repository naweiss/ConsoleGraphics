#include "Elements\Circle.h"
#include "Elements\Triangle.h"
#include "Elements\Square.h"

class DNA{
public:
	double fitness;
	int amount;
	Element** genes;
	
	DNA(ElementType type, int amount);
	
	DNA(Element** newgenes, int amount);
	
	~DNA();
	
	DNA* crossover(DNA* partner);
	
	void calaFitness(int x_offset, int y_offset);
	
	void mutation(float mutRate);
	
	void show(int x_offset, int y_offset);
	
	Image* getImg(int x_offset, int y_offset);
};