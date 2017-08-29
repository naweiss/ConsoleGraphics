#include "Population.h"
#include "Math.h"

ofstream myfile;

Population::Population(){
	for(int i=0;i<POP_SIZE;i++){
		rockets.push_back(Rocket());
	}
}

void Population::evaluate(){
	double maxfit = 0;
	double sum = 0;
	for(int i=0;i<POP_SIZE;i++){
		rockets[i].calaFitness();
		sum += rockets[i].fitness;
		if (rockets[i].fitness > maxfit)
			maxfit = rockets[i].fitness;
	}
	myfile << "fitness: " << sum/POP_SIZE << endl;
	for(int i=0;i<POP_SIZE;i++){
		rockets[i].fitness /= maxfit;
	}
	matingpool.clear();
	for(int i=0;i<POP_SIZE;i++){
		int x = rockets[i].fitness * 100;
		for(int j=0;j<x;j++)
			matingpool.push_back(rockets[i]);
	}
}

void Population::selection(){
	vector<Rocket> newrockets;
	for(int i=0;i<POP_SIZE;i++){
		DNA parentA = matingpool[Random(matingpool.size())].dna;
		DNA parentB = matingpool[Random(matingpool.size())].dna;
		DNA child = parentA.crossover(parentB);
		child.mutations();
		Rocket tmp;
		tmp.dna = child;
		newrockets.push_back(tmp);
	}
	rockets = newrockets;
}

void Population::run(){
	for(int i=0;i<POP_SIZE;i++){
		rockets[i].update();
		rockets[i].show();
	}
}