#include "DNA.h"
#include <iostream>

const float MUTATION_RATE = 0.01;

double color_dist(COLORREF color1,COLORREF color2){
	double r = pow((GetRValue(color1)-GetRValue(color2))/255.0,2);
	double g = pow((GetGValue(color1)-GetGValue(color2))/255.0,2);
	double b = pow((GetBValue(color1)-GetBValue(color2))/255.0,2);
	return sqrt((r + g + b)/3);
}

const int OFFSET = 20;
Image* img;
CharPool DNA::pool;

DNA::DNA(){
	for (int i = 0; i < ROWS; i++){
		int sum = 0;
		while(sum < WIDTH){
			char tmp = DNA::pool.rand();
			this->matrix[i].push_back(tmp);
			sum += (int)(getTextSize(&tmp,1).x);
		}
	}
}

void DNA::show(){
	background(RGB(255,255,255));
	for (int i = 0; i < ROWS; i++){
		int line_size = this->matrix[i].size();
		char *line = new char[line_size];
		copy(this->matrix[i].begin(), this->matrix[i].end(), line);
		drawText(OFFSET,OFFSET+SYMBOL_SIZE*i,line,line_size);
		delete[] line;
	}
}
	
DNA* DNA::crossover(DNA* partner){
	DNA* newElem = new DNA();
	for (int i = 0; i < ROWS; i++){
		int bigger = max(this->matrix[i].size(),partner->matrix[i].size());
		int smaller = min(this->matrix[i].size(),partner->matrix[i].size());
		for (int j = 0; j < smaller; j++){
			newElem->matrix[i][j] = RandomF(1) < 0.5 ? this->matrix[i][j] : partner->matrix[i][j];
		}
		for (int j = smaller; j < bigger; j++){
			newElem->matrix[i][j] = this->matrix[i].size() == bigger ? this->matrix[i][j] : partner->matrix[i][j];
		}
	}
	return newElem;
}

void DNA::mutation(){
	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < this->matrix[i].size(); j++){
			if (RandomF(1) < MUTATION_RATE){
				this->matrix[i][j] = DNA::pool.rand();
			}
		}
	}
}

void DNA::calaFitness(){
	Image* canvas = getImg();
	double sum = 0;
	for (int i=0;i<img->width;i++){
		for (int j=0;j<img->height;j++){
			sum += color_dist(canvas->get(i,j),img->get(i,j));
		}
	}
	delete canvas;
	this->fitness = sum / (img->width*img->height);
}

Image* DNA::getImg(){
	return GetCanvas(OFFSET+img->width,OFFSET+img->height,OFFSET,OFFSET);
}