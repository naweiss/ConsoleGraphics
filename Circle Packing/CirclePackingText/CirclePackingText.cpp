#include "Circle.h"
#include "Maths.h"
#include <vector>
#include <ctime>

vector<Circle> circles;
vector<Point> spots;
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
	unsigned int index = Random(spots.size());
	Point p(spots[index].x,spots[index].y);
	if(isInsideCircle(p)) return false;

	circles.push_back(Circle(p.x,p.y));
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

void findAvailableSpots(){
	int count = 0;
	for (int x=0;x<img->width;x+=2){
		for (int y=0;y<img->height;y+=2){
			COLORREF pixel = img->get(x,y);
			if (pixel > 0){
				spots.push_back(Point(x,y));
			}
		}		
	}
}

void setup(){
	srand(time(NULL));
	stroke(RGB(255,255,255));
	noFill();
	img = loadImage("BW.bmp");
	if (img == NULL){
		noLoop();
		return;
	}
	createCanvas(img->width,img-> height);
	findAvailableSpots();
}

void draw(){
	background();
	for (vector<Circle>::iterator c=circles.begin(); c != circles.end(); ++c){
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