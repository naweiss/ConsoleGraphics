#include "Graphics.h"
#include <vector>
using namespace std;

class Graph{	
public:
	enum Type{
		DOTED_LINES,
		LINES,
		DOTS
	};
	Point* max;
	Point* min;
	
	Graph(int n, int width,int height, int xOffset = 0, int yOffset = 0);
	
	void setMode(Graph::Type type);
	
	void setGensLimit(int limit);
	
	void addGen(vector<Point> points);
	
	void show();
private:
	int width;
	int height;
	int xOffset;
	int yOffset;
	int limit;
	int n;
	vector<Point>* lines;
	Graph::Type type;
	
	void calc();
};