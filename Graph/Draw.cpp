#include "Graph.h"
#include "Maths.h"
#include <ctime>

Graph* g;
int n = 10;

void setup(){
	srand(time(NULL));
	g = new Graph(n,500,250,50,50);
	g->setMode(Graph::LINES);
	// g->setMode(Graph::DOTS);
	g->setGensLimit(60);
}

void draw(){
	background();
	vector<Point> vec;
	for (int i = 0; i < n; i++)
			vec.push_back(Point(frameCount/10.0,sin(frameCount/10.0+i*HALF_PI/5)*100));
	g->addGen(vec);
	g->show();
	Sleep(200);
	// noLoop();
}