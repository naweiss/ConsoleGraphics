#include "DNA.h"
#include "Maths.h"

const int AMOUNT = 150;
const float MUTATION_RATE = 0.02;

double color_dist(COLORREF color1,COLORREF color2){
	double r = pow((GetRValue(color1)-GetRValue(color2))/255.0,2);
	double g = pow((GetGValue(color1)-GetGValue(color2))/255.0,2);
	double b = pow((GetBValue(color1)-GetBValue(color2))/255.0,2);
	return sqrt((r + g + b)/3);
}

DNA::DNA(){
	genes = new Square[AMOUNT];
}

DNA::DNA(Square* newgenes){
	genes = newgenes;
}

DNA::~DNA(){
	delete[] genes;
}

DNA* DNA::crossover(DNA* partner){
	Square* newgenes = new Square[AMOUNT];
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
	Image* canvas = GetCanvas(img->width,img->height);
	double sum = 0;
	for (int i=0;i<img->width;i++){
		for (int j=0;j<img->height;j++){
			sum += color_dist(canvas->get(i,j),img->get(i,j));
		}
	}
	delete canvas;
	return sum / (img->width*img->height);
}

void DNA::mutation(){
	for (int i=0;i<AMOUNT;i++){
		if (RandomF(1) < MUTATION_RATE){
			genes[i] = Square();
		}
	}
}

void DNA::show(){
	for (int i=0;i<AMOUNT;i++){
		genes[i].show();
	}
}