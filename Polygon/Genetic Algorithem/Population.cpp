#include "Pic.cpp"
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

const int POP_SIZE = 100;
ofstream myfile;
double bestFitness = 0;

class Population{
public:
	vector<Pic> pics;
	vector<Pic> matingpool;
	int generation;
	
	Population(){
		generation = 0;
		for(int i=0;i<POP_SIZE;i++){
			pics.push_back(Pic());
		}
	}
	
	void evaluate(short index){
		pics[index].calaFitness();
	}
	
	void evaluate(){
		double maxfit = 0;
		double sum = 0;
		for(int i=0;i<POP_SIZE;i++){
			sum += pics[i].fitness;
			if (pics[i].fitness > maxfit){
				maxfit = pics[i].fitness;
				if (pics[i].fitness > bestFitness){
					bestFitness = pics[i].fitness;
				}
			}
		}
		myfile << fixed << setprecision(4) << sum/POP_SIZE << "\t" << maxfit << endl;
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
		generation++;
	}
	
	void run(short index){
		pics[index].show();
	}
};