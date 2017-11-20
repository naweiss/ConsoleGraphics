#include "DNA.h"
#include "Maths.h"

const int AMOUNT = 30;
const float MUTATION_RATE = 0.02;

double color_dist(COLORREF color1,COLORREF color2){
	double r = pow((GetRValue(color1)-GetRValue(color2))/255.0,2);
	double g = pow((GetGValue(color1)-GetGValue(color2))/255.0,2);
	double b = pow((GetBValue(color1)-GetBValue(color2))/255.0,2);
	return sqrt((r + g + b)/3);
}

DNA::DNA(){
	genes = new Triangle[AMOUNT];
	my_img = NULL;
}
	
DNA::DNA(Triangle* newgenes){
	genes = newgenes;
	my_img = NULL;
}

DNA::~DNA(){
	delete[] genes;
	if (my_img)
		delete my_img;
}

DNA* DNA::crossover(DNA* partner){
	Triangle* newgenes = new Triangle[AMOUNT];
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
	double sum = 0;
	for (int i=0;i<img->width;i++){
		for (int j=0;j<img->height;j++){
			sum += color_dist(my_img->get(i,j),img->get(i,j));
		}
	}
	sum /= my_img->width*my_img->height;
	delete my_img;
	my_img = NULL;
	return sum;
}

void DNA::mutation(){
	for (int i=0;i<AMOUNT;i++){
		if (RandomF(1) < MUTATION_RATE){
			genes[i] = Triangle();
		}
	}
}

void DNA::show(){
	my_img = new Image(img->width, img->height, 3);
	for (int i=0;i<AMOUNT;i++){
		genes[i].show(my_img);
	}
	drawImage(my_img);
}