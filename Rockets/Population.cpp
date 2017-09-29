#include "Population.h"
#include "Graphics.h"
#include "Maths.h"
#include <string>

Population::Population(short id, float mutRate){
	this->mutRate = mutRate;
	this->id = id;
	log.open("Logs\\log_"+to_string(id)+".txt");
	log << "mutation rate: " << mutRate*100 << "%" << endl;
	for(int i=0;i<POP_SIZE;i++){
		rockets.push_back(new Rocket(mutRate));
	}
}

double Population::evaluate(){
	double maxfit = 0;
	double sum = 0;
	for(int i=0;i<POP_SIZE;i++){
		rockets[i]->calaFitness();
		sum += rockets[i]->fitness;
		if (rockets[i]->fitness > maxfit)
			maxfit = rockets[i]->fitness;
	}
	log << "fitness: " << sum/POP_SIZE << endl;
	for(int i=0;i<POP_SIZE;i++){
		rockets[i]->fitness /= maxfit;
	}
	for(int i=0;i<POP_SIZE;i++){
		int x = rockets[i]->fitness * 100;
		for(int j=0;j<x;j++)
			matingpool.push_back(rockets[i]);
	}
	return sum/POP_SIZE;
}

void Population::selection(){
	vector<Rocket*> newrockets;
	for(int i=0;i<POP_SIZE;i++){
		DNA parentA = matingpool[Random(matingpool.size())]->dna;
		DNA parentB = matingpool[Random(matingpool.size())]->dna;
		DNA child = parentA.crossover(parentB);
		child.mutations();
		Rocket* tmp = new Rocket(mutRate);
		tmp->dna = child;
		newrockets.push_back(tmp);
	}
	for(int i=0;i<POP_SIZE;i++){
		delete rockets[i];
	}
	matingpool.clear();
	rockets = newrockets;
}

void Population::run(){
	fill(rainbowColors(id*2));
	for(int i=0;i<POP_SIZE;i++){
		rockets[i]->update();
		rockets[i]->show();
	}
}