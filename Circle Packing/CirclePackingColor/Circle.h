#include "Graphics.h"
#include <iostream>
using namespace std;

class Circle{
private:
	Point center;
	COLORREF color;
	bool growing;
public:
	float radius;
	Circle(float x, float y,COLORREF color){
		this->center = Point(x,y);
		this->color = color;
		this->radius = 1;
		this->growing = true;
	}
	
	double dist(Point p){
		return sqrt(pow(center.x-p.x,2)+pow(center.y-p.y,2));
	}
	
	double dist(Circle c){
		return dist(c.center);
	}
	
	void stopGrow(){
		growing = false;
	}
	
	bool isGrowing(){
		return growing;
	}
	
	void grow(){
		if (growing)
			radius++;
	}
	
	bool hitEdges(){
		return (center.x+radius >= width || center.y+radius >= height ||
				center.x-radius <= 0 || center.y-radius <= 0);
	}
	
	void show(){
		fill(color);
		drawCircle(center.x,center.y,radius);
	}
};
