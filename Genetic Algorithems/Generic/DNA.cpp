#include "DNA.h"
#include "Maths.h"
#include <cmath>

double color_dist(COLORREF color1,COLORREF color2){
	double r = pow((GetRValue(color1)-GetRValue(color2))/255.0,2);
	double g = pow((GetGValue(color1)-GetGValue(color2))/255.0,2);
	double b = pow((GetBValue(color1)-GetBValue(color2))/255.0,2);
	return sqrt((r + g + b)/3);
}

/// TODO: handle another ElementTypes
DNA::DNA(ElementType type, int amount){
	this->fitness = 0;
	this->amount = amount;
	this->genes = new Element*[amount];
	for (int i=0;i<amount;i++){
		if (type == ElementType::SQUARE)
			genes[i] = new Square();
		if (type == ElementType::TRIANGLE)
			genes[i] = new Triangle();
		if (type == ElementType::CIRCLE)
			genes[i] = new Circle();
	}
}

DNA::DNA(Element** newgenes, int amount){
	this->fitness = 0;
	this->amount = amount;
	this->genes = newgenes;
}

DNA::~DNA(){
	delete[] genes;
}

/// TODO: try different crossovers
DNA* DNA::crossover(DNA* partner){
	Element** newgenes = new Element*[amount];
	int mid = amount/2;
	for (int i=0;i<amount;i++){
		if (i > mid){
			newgenes[i] = genes[i];
		} else {
			newgenes[i] = partner->genes[i];
		}
	}
	return new DNA(newgenes, amount);
}

void DNA::calaFitness(int x_offset, int y_offset){
	Image* canvas = this->getImg(x_offset, y_offset);
	double sum = 0;
	for (int i=0;i<originalImg->width;i++){
		for (int j=0;j<originalImg->height;j++){
			sum += color_dist(canvas->get(i,j), originalImg->get(i,j));
		}
	}
	delete canvas;
	fitness = 1 - (sum / (originalImg->width*originalImg->height));
}

void DNA::mutation(float mutRate){
	for (int i=0;i<amount;i++){
		if (RandomF(1) < mutRate){
			genes[i]->mutate();
		}
	}
}

Image* DNA::getImg(int x_offset, int y_offset){
	return GetCanvas(originalImg->width + x_offset, originalImg->height + y_offset, x_offset, y_offset);
}

/// TODO: handle alpha
void DNA::show(int x_offset, int y_offset){
	for (int i=0;i<amount;i++){
		//alpha(200);
		genes[i]->show(x_offset, y_offset);
		//alpha(255);
	}
}