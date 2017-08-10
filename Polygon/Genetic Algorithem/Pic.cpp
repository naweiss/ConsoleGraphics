#include "Triangle.cpp"
#include <vector>

const int AMOUNT = 15;
Image* img;

double color_dist(COLORREF color1,COLORREF color2){
	double r = GetRValue(color1)-GetRValue(color2);
	double g = GetGValue(color1)-GetGValue(color2);
	double b = GetBValue(color1)-GetBValue(color2);
	return pow((r/255 + g/255 + b/255)/3,2);
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
		int mid = Random(AMOUNT);
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
			if (RandomF(1) < 0.01){
				genes[i] = Triangle();
			}
		}
	}
	
	void calaFitness(){
		double sum = 0;
		for (int i=0;i<img->width;i++){
			for (int j=0;j<img->height;j++){
				sum += color_dist(img->get(i,j),GetPixelC(i,j));
			}
		}
		fitness = 1/sum;
	}
	
	void show(){
		background();
		for (int i=0;i<AMOUNT;i++){
			genes[i].show();
		}
	}
};