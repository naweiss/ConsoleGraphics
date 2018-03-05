#include "Circle.h"
#include "Maths.h"
#include <vector>
#include <ctime>

vector<Circle> circles;
Image* img = NULL;

bool isInsideCircle(Point p){
	for (vector<Circle>::iterator c=circles.begin();
		 c != circles.end();
		 ++c){
		if (c->dist(p) <= c->radius)
			return true;
	}
	return false;
}

bool newCircleCreated(){
	Point p(Random(width),Random(height));
	if(isInsideCircle(p)) return false;
	
	circles.push_back(Circle(p.x,p.y,img->get(p.x,p.y)));
	return true;
}

void addNewCircles(){
	int total = 40;
	int count = 0;
	int attempts = 0;
	
	while(count < total){
		if (newCircleCreated()){
			count++;
		}
		if (++attempts > total*10){
			SaveBMP(GetCanvas(),"ans.bmp");
			noLoop();
			return;
		}
	}
}

void handleCollisions(vector<Circle>::iterator c){
	for (vector<Circle>::iterator other=circles.begin();
		 other != circles.end();
		 ++other){
		if (other == c)
			continue;
		if (c->dist(*other) - 1 <= c->radius + other->radius){
			c->stopGrow();
			break;
		}
	}
}

void setup(){
	srand(time(NULL));
	noStroke();
	img = loadImage("kitten.bmp");
	if (img == NULL){
		noLoop();
		return;
	}
	createCanvas(img->width,img-> height);
}

void draw(){
	background();
	for (vector<Circle>::iterator c=circles.begin();
		 c != circles.end();
		 ++c){
		if (c->isGrowing()){
			if (c->hitEdges()){
				c->stopGrow();
			} else {
				handleCollisions(c);
			}
		}
		c->show();
		c->grow();
	}
	addNewCircles();
}