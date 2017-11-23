#include "Population.h"
#include "Maths.h"
#include <string>
#include <iomanip>

void Population::free(){
	this->matingpool.clear();
	for(int i=0;i<this->size;i++){
		delete this->dnas[i];
	}
	delete[] this->dnas;
}

Population::Population(int id, int size, int amount, ElementType type, float mutRate){
	this->id = id;
	this->mutRate = mutRate;
	this->bestImg = NULL;
	this->bestFitness = 0;
	this->maxFitness = 0;
	this->avgFitness = 0;
	this->size = size;
	this->dnas = new DNA*[size];
	for(int i=0;i<size;i++){
		this->dnas[i] = new DNA(type, amount);
	}
}

Population::~Population(){
	this->free();
}

void Population::evaluate(short index){
	int y_offset = (this->id / (width / originalImg->width))*originalImg->height, x_offset = (this->id % (width / originalImg->width)) * originalImg->width;
	this->dnas[index]->calaFitness(x_offset, y_offset);
	if (this->dnas[index]->fitness > bestFitness){
		this->bestFitness = this->dnas[index]->fitness;
		if (this->bestImg)
			delete this->bestImg;
		this->bestImg = this->dnas[index]->getImg(x_offset, y_offset);
	}
}

void Population::evaluate(){
	double maxfit = 0, sum = 0;
	for(int i=0;i<this->size;i++){
		sum += dnas[i]->fitness;
		if (dnas[i]->fitness > maxfit){
			maxfit = dnas[i]->fitness;
		}
	}
	this->maxFitness = maxfit;
	this->avgFitness = sum / size;
	for(int i=0;i<this->size;i++){
		this->dnas[i]->fitness /= maxfit;
	}
	for(int i=0;i<this->size;i++){
		int x = (int)(this->dnas[i]->fitness * 100);
		for(int j=0;j<x;j++)
			this->matingpool.push_back(this->dnas[i]);
	}
}

void Population::selection(){
	DNA** newdnas = new DNA*[this->size];
	int POOL_SIZE = this->matingpool.size();
	for(int i=0;i<this->size;i++){
		DNA* parentA = this->matingpool[Random(POOL_SIZE)];
		DNA* parentB = this->matingpool[Random(POOL_SIZE)];
		DNA* child = parentA->crossover(parentB);
		child->mutation(this->mutRate);
		newdnas[i] = child;
	}
	free();
	this->dnas = newdnas;
}

void Population::run(short index){
	int y_offset = (this->id / (width / originalImg->width))*originalImg->height, x_offset = (this->id % (width / originalImg->width)) * originalImg->width;
	dnas[index]->show(x_offset, y_offset);
}

void Population::saveBest(const char* path, const char* file_name, const char* type)
{
	string passed = string(path) + "/" + string(file_name) +"_"+ string(type) +"_" + to_string(mutRate) + "_"+ to_string(bestFitness) + ".bmp";
	SaveBMP(this->bestImg, passed.c_str());
}