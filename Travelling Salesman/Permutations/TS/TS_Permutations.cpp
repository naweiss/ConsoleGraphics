#include "Graphics.h"
#include "Maths.h"
#include <string>
#include <ctime>
using namespace std;

static const int POINT_SIZE = 8;
static double recordDistance = -1;
static Point cities[POINT_SIZE];
static Point bestEver[POINT_SIZE];
static int order[POINT_SIZE];
static int cities_count = 1;
static long totalPermutations = 0;

void swap(Point& p1,Point& p2){
	Point tmp = p1;
	p1 = p2;
	p2 = tmp;
}

void Reverse(int start,int end){
	for (int i = start; i <= start+(end-start)/2; i++){
		swap(order[i],order[end-(i-start)]);
	}
}

double dist(Point p1,Point p2){
	return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

void UpdateCities(){
	for (int i =0;i < POINT_SIZE;i++){
		bestEver[i] = cities[order[i]];
	}
}

double calcDistance(){
	double sum = 0;
	for(int i=0;i < POINT_SIZE-1;i++)
	{
		sum += dist(cities[order[i]],cities[order[i+1]]);
	}
	return sum;
}

void nextOrder(){
	cities_count++;	
	int largestI = -1;
	for (int i = 0; i < POINT_SIZE-1; i++){
		if (order[i] <order[i+1])
			largestI = i;
	}
	if(largestI == -1){
		noLoop();
		return;
	}
	int largestJ = -1;
	for (int j = 0; j < POINT_SIZE; j++){
		if (order[largestI] < order[j])
			largestJ = j;
	}
	
	swap(order[largestI],order[largestJ]);
	
	Reverse(largestI+1,POINT_SIZE-1);
}

int factorial(int n){
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

void setup(){
	srand (time(NULL));
	for (int i = 0; i < POINT_SIZE; i++){
		cities[i].x = Random(20,width/3+20);
		cities[i].y = Random(20,height/2);
		cities[i].color = rainbowColors(i);
		order[i] = i;
	}
	
	recordDistance = calcDistance();
	UpdateCities();
	totalPermutations = factorial(POINT_SIZE);
}

void draw(){
	background();
	
	
	int percent = (10000 * cities_count / totalPermutations);
	string str = to_string(percent/100.0);
	str += "% completed";
	drawText(0,0,str.c_str(),str.length());
	
	noFill();
	stroke(RGB(255,255,255));
	beginShape();
	for (int i = 0; i < POINT_SIZE; i++){
		vertex(cities[order[i]]);
	}
		
	noStroke();
	for (int i = 0; i < POINT_SIZE; i++){
		fill(cities[i].color);
		drawEllipse(cities[i].x,cities[i].y,4,4);
	}
	
	noFill();
	stroke(RGB(150,0,150));
	beginShape();
	for (int i = 0; i < POINT_SIZE; i++){
		Point tmp = bestEver[i];
		tmp.x += width/3;
		vertex(tmp);
	}
	
	noStroke();
	fill();
	for (int i = 0; i < POINT_SIZE; i++){
		drawEllipse(cities[i].x+width/3,cities[i].y,4,4);
	}
	
	double d = calcDistance();
	if (d < recordDistance)
	{
		recordDistance = d;
		UpdateCities();
	}
	
	// fill(RGB(0,255,0));
	// for (int i = 0; i < POINT_SIZE; i++){
		// str = "("+to_string(cities[i].x)+","+to_string(cities[i].y)+")";
		// drawText(cities[i].x+width/3,cities[i].y+5,str.c_str(),str.length());
	// }
	
	nextOrder();
}