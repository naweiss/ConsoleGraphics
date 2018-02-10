#include "Graphics.h"
#include "Maths.h"

extern Image* img;

class DNA{
public:
	BYTE* genes;
	int size;

	DNA();
	
	~DNA();
	
	DNA* crossover(DNA* partner);
	
	void mutation();
	
	double dist();
	
	void show();
};