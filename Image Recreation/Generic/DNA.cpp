#include "DNA.h"
#include "Maths.h"
#include <iostream>

Image* img;
const int DNA::AMOUNT = 10;

double color_dist(COLORREF color1,COLORREF color2){
	double r = std::pow((GetRValue(color1)-GetRValue(color2))/255.0,2);
	double g = std::pow((GetGValue(color1)-GetGValue(color2))/255.0,2);
	double b = std::pow((GetBValue(color1)-GetBValue(color2))/255.0,2);
	return std::sqrt((r + g + b)/3);
}

DNA::DNA(){
	genes = new Element*[AMOUNT];
	for (int i=0;i<AMOUNT;i++){
		genes[i] = new Square();
	}
}

DNA::DNA(Element** newgenes){
	genes = newgenes;
}

DNA::~DNA(){
	delete[] genes;
}

DNA* DNA::crossover(DNA* partner){
	Element** newgenes = new Element*[AMOUNT];
	int mid = AMOUNT/2;
	for (int i=0;i<AMOUNT;i++){
		if (i > mid){
			newgenes[i] = genes[i];
		} else {
			newgenes[i] = partner->genes[i];
		}
	}
	return new DNA(newgenes);
}

double DNA::calaFitness(){
	Image* canvas = this->getImg();
	double sum = 0;
	for (int i=0;i<img->width;i++){
		for (int j=0;j<img->height;j++){
			sum += color_dist(canvas->get(i,j),img->get(i,j));
		}
	}
	delete canvas;
	return sum / (img->width*img->height);
}

void DNA::mutation(float mutRate){
	for (int i=0;i<AMOUNT;i++){
		if (RandomF(1) < mutRate){
			genes[i]->mutate();
		}
	}
}

Image* DNA::getImg(){
	return GetCanvas(img->width,img->height);
}

void DNA::show(){
	for (int i=0;i<AMOUNT;i++){
		genes[i]->show();
	}
}