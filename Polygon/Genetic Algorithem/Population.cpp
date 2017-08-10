#include "Pic.cpp"
#include <vector>
#include <string>
#include <fstream>

const int POP_SIZE = 40;
ofstream myfile;

class Population{
public:
	vector<Pic> pics;
	vector<Pic> matingpool;
	
	Population(){
		for(int i=0;i<POP_SIZE;i++){
			pics.push_back(Pic());
		}
	}
	
	void evaluate(){
		double maxfit = 0;
		for(int i=0;i<POP_SIZE;i++){
			pics[i].calaFitness();
			if (pics[i].fitness > maxfit)
				maxfit = pics[i].fitness;
		}
		myfile << "fitness: " << maxfit << endl;
		for(int i=0;i<POP_SIZE;i++){
			pics[i].fitness /= maxfit;
		}
		matingpool.clear();
		for(int i=0;i<POP_SIZE;i++){
			int x = pics[i].fitness * 100;
			for(int j=0;j<x;j++)
				matingpool.push_back(pics[i]);
		}
	}
	
	void selection(){
		vector<Pic> newpics;
		for(int i=0;i<POP_SIZE;i++){
			Pic parentA = matingpool[Random(matingpool.size())];
			Pic parentB = matingpool[Random(matingpool.size())];
			Pic child = parentA.crossover(parentB);
			child.mutation();
			newpics.push_back(child);
		}
		pics = newpics;
	}
	
	void run(short index){
		pics[index].show();
	}
};