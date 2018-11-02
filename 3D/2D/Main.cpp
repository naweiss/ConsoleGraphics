#include "Graphics.h"
#include "Maths.h"
#include <math.h>
#include <iostream>

int size = 200, offset = 0;
float angle = 0;
Point points[4];

float radians(float angle) {
	return angle * PI / 180.0;
}

void rotate2d(float angle) {
	Point p;
	for (int i = 0; i < 4; i++) {
		p = points[i];
		points[i] = Point(p.x * cos(radians(angle)) - p.y * sin(radians(angle)),
				 p.x * sin(radians(angle)) + p.y * cos(radians(angle)));
	}
}

void translate2d(float x, float y) {
	Point p;
	for (int i = 0; i < 4; i++) {
		p = points[i];
		points[i] = Point(p.x + x, p.y + y);
	}
}

void setup() {
	createCanvas();
	points[0] = Point(-size, -size);
	points[1] = Point(-size, size);
	points[2] = Point(size,  size);
	points[3] = Point(size, -size);
}

void draw() {
	background();
	
	rotate2d(angle);
	translate2d(width/2 , height/2);
	
	beginShape();
	for (int i = 0; i < 5; i++)
		vertex(points[i % 4]);
	
	translate2d(-width/2 , -height/2);
	rotate2d(-angle);
	
	angle += 1;
}