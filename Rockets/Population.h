#include "Rocket.h"
#include <vector>
#include <fstream>

extern ofstream myfile;

class Population{
	const int POP_SIZE = 100;
public:
	vector<Rocket> rockets;
	vector<Rocket> matingpool;
	Population();
	
	void evaluate();
	
	void selection();
	
	void run();
};