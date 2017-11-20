#include "Population.h"
#include "Maths.h"
#include <string>
#include <iomanip>

const int Population::POP_SIZE = 150;

void Population::free(){
	for(int i=0;i<POP_SIZE;i++){
		delete this->pics[i];
	}
	delete[] this->pics;
}

Population::Population(short id, float mutRate){
	log.open("Logs/log_halfs.txt");
	this->generation = 0;
	this->id = id;
	this->mutRate = mutRate;
	this->bestImg = NULL;
	this->bestFitness = 0;
	this->pics = new Pic*[POP_SIZE];
	for(int i=0;i<POP_SIZE;i++){
		this->pics[i] = new Pic();
	}
}

Population::~Population(){
	this->free();
}

void Population::evaluate(short index){
	this->pics[index]->calaFitness();
	if (this->pics[index]->fitness > bestFitness){
		bestFitness = this->pics[index]->fitness;
		if (bestImg)
			delete bestImg;
		bestImg = GetCanvas(img->width,img->height);
	}
}

void Population::evaluate(){
	double maxfit = 0;
	double sum = 0;
	for(int i=0;i<POP_SIZE;i++){
		double current = pics[i]->fitness;
		sum += current;
		if (current > maxfit){
			maxfit = current;
		}
	}
	this->log << fixed << setprecision(4) << sum/POP_SIZE << "\t" << maxfit << endl;																	  
	for(int i=0;i<POP_SIZE;i++){
		this->pics[i]->fitness /= maxfit;
	}
	this->matingpool.clear();
	for(int i=0;i<POP_SIZE;i++){
		int x = this->pics[i]->fitness * 100;
		for(int j=0;j<x;j++)
			this->matingpool.push_back(this->pics[i]);
	}
}

void Population::selection(){
	Pic** newpics = new Pic*[POP_SIZE];
	int POOL_SIZE = this->matingpool.size();
	for(int i=0;i<POP_SIZE;i++){
		DNA* parentA = this->matingpool[Random(POOL_SIZE)]->dna;
		DNA* parentB = this->matingpool[Random(POOL_SIZE)]->dna;
		DNA* child = parentA->crossover(parentB);
		child->mutation(this->mutRate);
		newpics[i] = new Pic(child);
	}
	free();
	this->pics = newpics;
	generation++;
}

void Population::run(short index){
	pics[index]->show();
}