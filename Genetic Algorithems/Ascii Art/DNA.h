#include "Graphics.h"
#include "CharPool.h"
#include <vector>
using namespace std;

static const int WIDTH = 350;
static const int HEIGHT = 250;
static const int SYMBOL_SIZE = 18;
static const int ROWS = HEIGHT/SYMBOL_SIZE;
extern const int OFFSET;
extern Image* img;

class DNA{
	float mutRate;
	static CharPool pool;
	vector<char> matrix[ROWS];
public:
	float fitness;
	
	DNA();
		
	DNA* crossover(DNA* partner);
	void calaFitness();
	Image* getImg();
	void show();
	void mutation();
};