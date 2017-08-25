#include "Graph.cpp"
#include "Math.cpp"
#include <ctime>

Graph* g;
int n = 8;

void setup(){
	srand(time(NULL));
	g = new Graph(n,500,250,50,50);
	// g->setMode(Graph::DOTS);
	g->setGensLimit(20);
}

void draw(){
	background();
	vector<Point> vec;
	for (int i = 0; i < n; i++)
			vec.push_back(Point(frameCount,sin(frameCount+i*HALF_PI/2)*100));
	g->addGen(vec);
	g->show();
	Sleep(500);
	// noLoop();
}