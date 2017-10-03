#include "DNA.h"

const float MUTATION_RATE = 0.01;
Image* img;

DNA::DNA(){
	this->size = img->width*img->height;
	genes = new BYTE[size];
	for(long i=0;i<size;i++){
		genes[i] = Random(2) == 1 ? 255 : 0;
	}
}

DNA::~DNA(){
	delete[] genes;
}

DNA* DNA::crossover(DNA* partner){
	DNA* new_dna = new DNA;
	int mid = Random(this->size);
	for (int i=0;i<this->size;i++){
		if (i > mid)
			new_dna->genes[i] = genes[i];
		else
			new_dna->genes[i] = partner->genes[i];
	}
	return new_dna;
}

void DNA::mutation(){
	for (int i=0;i<this->size;i++){
		if (RandomF(1) < MUTATION_RATE){
			genes[i] = Random(2) == 1 ? 255 : 0;
		}
	}
}

double DNA::dist(){
	double sum = 0;
	for(long i=0;i<this->size;i++){
		sum += abs(img->pixels[i*img->Bpp]-genes[i]);
	}
	return (sum/255)/size;
}

void DNA::show(){
	for(int i=0;i<img->width;i++){
		for(int j=0;j<img->height;j++){
			int index = (i*img->width)+j;
			fill(RGB(genes[index],genes[index],genes[index]));
			SetPixelC(i,j);
		}
	}
}