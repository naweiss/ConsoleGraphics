#include "Graphics.h"
#include "Maths.h"
#include <math.h>
#include <iostream>

int size = 150, offset = 0;
float angle = 0;

float radians(float angle) {
	return angle * PI / 180.0;
}

Point translate2d(const Point& p, float x, float y) {
	return Point(p.x + x, p.y + y);
}

Point projecte2d(const Point& p) {
	// Perspective
	// float distance = 3;
	// float z = 1 / (distance - (p.z / size));
	// return Point(p.x * z, p.y * z);
	
	// Regular
	return Point(p.x, p.y);
	
}

Point rotate3dX(const Point& p, float angle) {
	return Point(p.x,
				 p.y * cos(radians(angle)) - p.z * sin(radians(angle)),
				 p.y * sin(radians(angle)) + p.z * cos(radians(angle)));
}

Point rotate3dY(const Point& p, float angle) {
	return Point(p.x * cos(radians(angle)) + p.z * sin(radians(angle)),
				 p.y,
				 - p.x * sin(radians(angle)) + p.z * cos(radians(angle)));
}

Point rotate3dZ(const Point& p, float angle) {
	return Point(p.x * cos(radians(angle)) - p.y * sin(radians(angle)),
				 p.x * sin(radians(angle)) + p.y * cos(radians(angle)),
				 p.z);
}

Point points[8];

void setup() {
	createCanvas();
	points[0] = Point(-size, -size, -size);
	points[1] = Point(-size,  size, -size);
	points[2] = Point(size,   size, -size);
	points[3] = Point(size,  -size, -size);
	points[4] = Point(-size, -size,  size);
	points[5] = Point(-size,  size,  size);
	points[6] = Point(size,   size,  size);
	points[7] = Point(size,  -size,  size);
}

void draw() {
	background();
	
	beginShape();
	for (int i = 0; i < 5; i++) {
		Point p = rotate3dZ(rotate3dY(rotate3dX(points[i % 4], angle), angle), angle);
		vertex(translate2d(projecte2d(p), width/2 , height/2));
	}
	
	beginShape();
	for (int i = 0; i < 5; i++) {
		Point p = rotate3dZ(rotate3dY(rotate3dX(points[4 + i % 4], angle), angle), angle);
		vertex(translate2d(projecte2d(p), width/2 , height/2));
	}
	
	for (int i = 0; i < 4; i++) {
		beginShape();
		Point p1 = rotate3dZ(rotate3dY(rotate3dX(points[i], angle), angle), angle);
		Point p2 = rotate3dZ(rotate3dY(rotate3dX(points[4 + i], angle), angle), angle);
		vertex(translate2d(projecte2d(p1), width/2 , height/2));
		vertex(translate2d(projecte2d(p2), width/2 , height/2));
	}
	
	angle += 1;
}