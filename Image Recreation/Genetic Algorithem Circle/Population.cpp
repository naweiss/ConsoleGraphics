#include "Population.h"
#include "Maths.h"
#include <string>
#include <iomanip>

const int POP_SIZE = 300;
double bestFitness = 0;
ofstream myfile;
Image* bestImg;

void Population::free(){
	for(int i=0;i<POP_SIZE;i++){
		delete pics[i];
	}
	delete[] pics;
}

Population::Population(){
	generation = 0;
	pics = new Pic*[POP_SIZE];
	for(int i=0;i<POP_SIZE;i++){
		pics[i] = new Pic();
	}
}

Population::~Population(){
	free();
}

void Population::evaluate(short index){
	pics[index]->calaFitness();
	if (pics[index]->fitness > bestFitness){
		bestFitness = pics[index]->fitness;
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
	myfile << fixed << setprecision(4) << sum/POP_SIZE << "\t" << maxfit << endl;																	  
	for(int i=0;i<POP_SIZE;i++){
		pics[i]->fitness /= maxfit;
	}
	matingpool.clear();
	for(int i=0;i<POP_SIZE;i++){
		int x = pics[i]->fitness * 100;
		for(int j=0;j<x;j++)
			matingpool.push_back(pics[i]);
	}
}

void Population::selection(){
	Pic** newpics = new Pic*[POP_SIZE];
	for(int i=0;i<POP_SIZE;i++){
		DNA* parentA = matingpool[Random(matingpool.size())]->dna;
		DNA* parentB = matingpool[Random(matingpool.size())]->dna;
		DNA* child = parentA->crossover(parentB);
		child->mutation();
		newpics[i] = new Pic(child);
	}
	free();
	pics = newpics;
	generation++;
}

void Population::run(short index){
	pics[index]->show();
}