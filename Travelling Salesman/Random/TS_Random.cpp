#include "Graphics.cpp"
#include "Math.cpp"
#include <ctime>

static const int POINT_SIZE = 10;
static double recordDistance = -1;
static Point cities[POINT_SIZE];
static Point bestEver[POINT_SIZE];

void swap(Point& p1,Point& p2){
	Point tmp = p1;
	p1 = p2;
	p2 = tmp;
}

double dist(Point p1,Point p2){
	return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

void UpdateCities()
{
	for (int i =0;i < POINT_SIZE;i++){
		bestEver[i] = cities[i];
	}
}

double calcDistance(){
	double sum = 0;
	for(int i=0;i < POINT_SIZE-1;i++)
	{
		sum += dist(cities[i],cities[i+1]);
	}
	return sum;
}

void setup(){
	srand (time(NULL));
	for (int i = 0; i < POINT_SIZE; i++){
		cities[i].x = Random(20,width/3);
		cities[i].y = Random(20,height/2);
		cities[i].color = rainbowColors(i);
	}
	recordDistance = calcDistance();
	UpdateCities();
}

void draw(){
	background();
	
	noFill();
	stroke(RGB(255,255,255));
	beginShape();
	for (int i = 0; i < POINT_SIZE; i++){
		vertex(cities[i]);
	}
	
	stroke(RGB(150,0,150));
	beginShape();
	for (int i = 0; i < POINT_SIZE; i++){
		Point tmp = bestEver[i];
		tmp.x += width/3;
		vertex(tmp);
	}
	
	noStroke();
	for (int i = 0; i < POINT_SIZE; i++){
		fill(cities[i].color);
		drawEllipse(cities[i].x,cities[i].y,4,4);
		fill();
		drawEllipse(cities[i].x+width/3,cities[i].y,4,4);
	}
	
	int i =  Random(POINT_SIZE);
	int j =  Random(POINT_SIZE);
	swap(cities[i],cities[j]);
	
	double d = calcDistance();
	if (d < recordDistance)
	{
		recordDistance = d;
		UpdateCities();
	}
	
}