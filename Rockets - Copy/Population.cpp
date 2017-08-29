#include "Rocket.cpp"
#include <vector>
#include <fstream>

ofstream myfile;

class Population{
	const int POP_SIZE = 100;
public:
	vector<Rocket> rockets;
	vector<Rocket> matingpool;
	Population(){
		for(int i=0;i<POP_SIZE;i++){
			rockets.push_back(Rocket());
		}
	}
	
	void evaluate(){
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
	
	void selection(){
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
	
	void run(){
		for(int i=0;i<POP_SIZE;i++){
			rockets[i].update();
			rockets[i].show();
		}
	}
};