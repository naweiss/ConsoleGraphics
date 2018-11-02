#include "Graphics.h"
#include "Maths.h"
#include <algorithm>
#include <ctime>

int* arr;
int scale = 15;
int len, i = 0, j = 0;

void bubbleSortStep() {
	if (arr[j] > arr[j+1])
		std::swap(arr[j], arr[j+1]);
	j++;
	
	if (j >= len - 1 - i) {
		j = 0;
		i++;
		if (i >= len)
			noLoop();
	}
	
}

void showArray() {
	for (int k = 0; k < len; k++) {		
		if (k == j)
			fill(RGB(100, 255, 0));
		else if (k >= len - i)
			fill(RGB(100, 100, 100));
		else
			fill(RGB(255, 255, 255));
		drawRectangle((k+0.25)*scale, height - arr[k], scale/2, arr[k]);
	}
}

void setup() {
	srand(time(NULL));
	createCanvas(400, 400);
	
	len = width/scale;
	arr = new int[len];
	for (int i = 0; i < len; i++)
		arr[i] = Random(1, height/scale)*scale;
}

void draw() {
	background();
	
	bubbleSortStep();
	showArray();
}