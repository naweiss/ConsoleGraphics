#include "Graphics.h"
#include "Maths.h"
#include <math.h>

int size = 150, offset = 0;
float angle = 0;

float radians(float angle) {
	return angle * PI / 180.0;
}

Point translate2d(const Point& p, float x, float y) {
	return Point(p.x + x, p.y + y);
}

Point projecte2d(const Point& p) {
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

const static int total = 15;
const static float radius = 200;
Point points[total+1][total+1];

void setup() {
	createCanvas();
	for (int i = 0; i < total + 1; i++) {
		float lat = (float)i / total * PI;
		for (int j = 0; j < total + 1; j++) {
			float lon = (float)j / total * TWO_PI;
			float x = radius * sin(lat) * cos(lon);
			float y = radius * sin(lat) * sin(lon);
			float z = radius * cos(lat);
			points[i][j] = Point(x, y, z);
		}
	}
}

void draw() {
	background();
	
	for (int i = 0; i < total; i++) {
		for (int j = 0; j < total; j++) {
			Point p1 = points[i][j];
			Point p2 = points[i + 1][j];
			Point p3 = points[i][j + 1];
			
			p1 = rotate3dZ(rotate3dY(rotate3dX(p1, angle), angle), angle);
			p2 = rotate3dZ(rotate3dY(rotate3dX(p2, angle), angle), angle);
			p3 = rotate3dZ(rotate3dY(rotate3dX(p3, angle), angle), angle);
			
			p1 = translate2d(projecte2d(p1), width/2, height/2);
			p2 = translate2d(projecte2d(p2), width/2, height/2);
			p3 = translate2d(projecte2d(p3), width/2, height/2);
			
			drawLine(p1.x, p1.y, p2.x, p2.y);
			drawLine(p1.x, p1.y, p3.x, p3.y);
			drawLine(p2.x, p2.y, p3.x, p3.y);
		}
	}
	
	angle += 1;
}