#include "Graphics.h"
#include "Maths.h"
#include <ctime>
#include <iostream>
using namespace std;

int x = 0, y = 0, spacing = 15;

void setup(){
	createCanvas();
	background(RGB(200,200,200));
	srand(time(NULL));
}

void draw(){
	stroke(RGB(255,255,255));
	if (RandomF(1) < 0.1) {
		drawLine(x, y, x + spacing, y + spacing);
	} else {
		drawLine(x, y + spacing, x + spacing, y);
	}
	x = x + spacing;
	if (x > width) {
		x = 0;
		y = y + spacing;
	}
	if (y > height){
		noLoop();
	}
}