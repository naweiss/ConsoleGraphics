#include "DNA.cpp"
#include <vector>

Image* img;

double color_dist(COLORREF color1,COLORREF color2){
	double r = abs(GetRValue(color1)-GetRValue(color2));
	double g = abs(GetGValue(color1)-GetGValue(color2));
	double b = abs(GetBValue(color1)-GetBValue(color2));
	return (r + g + b)/3/255;
}

class Pic{
public:
	DNA* dna;
	double fitness;
	
	Pic(){
		dna = new DNA;
		fitness = 0;
	}
	
	Pic(DNA* new_dna){
		fitness = 0;
		dna = new_dna;
	}
	
	~Pic(){
		delete dna;
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
		dna->show();
	}
};