#include "Graph.h"
#include "Maths.h"
#include <ctime>

Graph* g;
int n = 10;

void setup(){
	lineThickness(2);
	srand(time(NULL));
	createCanvas();
	g = new Graph(n,700,400,50,20);
	g->setMode(Graph::LINES);
	// g->setMode(Graph::DOTS);
	g->setGensLimit(100);
}

void draw(){
	background();
	vector<Point> vec;
	float x = frameCount*1.0/n;
	for (int i = 0; i < n; i++){
		/** f(x,i) = 100*sin(x+i*PI/n) **/
		vec.push_back(Point(x,sin(x+i*PI/n)*100));
	}
	g->addGen(vec);
	g->show();
	Sleep(200);
	// noLoop();
}