#include "Square.h"

extern Image* img;

class DNA{
	static const int AMOUNT;
public:
	Element** genes;
	
	DNA();
	
	DNA(Element** newgenes);
	
	~DNA();
	
	DNA* crossover(DNA* partner);
	
	double calaFitness();
	
	void mutation(float mutRate);
	
	void show();
	
	Image* getImg();
};