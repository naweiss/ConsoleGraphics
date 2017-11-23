#include "Rocket.h"
#include <vector>
#include <fstream>

class Population{
	const int POP_SIZE = 100;
	short id;
	float mutRate;
	ofstream log;
public:
	vector<Rocket*> rockets;
	vector<Rocket*> matingpool;
	Population(short id, float mutRate);
	
	double evaluate();
	
	void selection();
	
	void run();
};