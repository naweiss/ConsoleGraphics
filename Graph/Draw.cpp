#include "Graph.cpp"
#include "Math.cpp"
#include <ctime>

Graph* g;
int n = 4;

void setup(){
	srand(time(NULL));
	g = new Graph(n,1200,500,50,50);
	vector<Point> vec;
	for (int i = 0; i < n; i++)
		vec.push_back(Point(-1000,RandomF(-1000,1000)));
	g->addGen(vec);
}

void draw(){
	background();
	g->show();
	Sleep(500);
	vector<Point> vec;
	for (int i = 0; i < n; i++)
		vec.push_back(Point(frameCount*100-1000,RandomF(-1000,1000)));
	g->addGen(vec);
	// noLoop();
}