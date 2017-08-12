#include "Triangle.cpp"
#include <vector>

const int AMOUNT = 15;
const float MUTATION_RATE = 0.02;
Image* img;

double color_dist(COLORREF color1,COLORREF color2){
	double r = abs(GetRValue(color1)-GetRValue(color2));
	double g = abs(GetGValue(color1)-GetGValue(color2));
	double b = abs(GetBValue(color1)-GetBValue(color2));
	return (r + g + b)/3/255;
}

class Pic{
public:
	vector<Triangle> genes;
	double fitness;
	Pic(){
		fitness = 0;
		for (int i=0;i<AMOUNT;i++){
			genes.push_back(Triangle());
		}
	}
	
	Pic(vector<Triangle> newgenes){
		fitness = 0;
		genes = newgenes;
	}
	
	Pic crossover(Pic partner){
		vector<Triangle> newgenes;
		int mid = AMOUNT/2;
		for (int i=0;i<AMOUNT;i++){
			if (i > mid){
				newgenes.push_back(genes[i]);
			} else {
				newgenes.push_back(partner.genes[i]);
			}
		}
		return Pic(newgenes);
	}
	
	void mutation(){
		for (int i=0;i<AMOUNT;i++){
			if (RandomF(1) < MUTATION_RATE){
				genes[i] = Triangle();
			}
		}
	}
	
	void calaFitness(){
		Image* canvas = GetCanvas();
		double sum = 0;
		for (int i=0;i<img->width;i++){
			for (int j=0;j<img->height;j++){
				sum += color_dist(img->get(i,j),canvas->get(i,j));
			}
		}
		delete canvas;
		sum /= img->width*img->height;
		fitness = 1-sum;
	}
	
	void show(){
		background();
		for (int i=0;i<AMOUNT;i++){
			genes[i].show();
		}
	}
};