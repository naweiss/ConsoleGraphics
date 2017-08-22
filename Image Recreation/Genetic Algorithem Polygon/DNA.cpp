#include "Triangle.cpp"

const int AMOUNT = 15;
const float MUTATION_RATE = 0.02;

double color_dist(COLORREF color1,COLORREF color2){
	double r = abs(GetRValue(color1)-GetRValue(color2));
	double g = abs(GetGValue(color1)-GetGValue(color2));
	double b = abs(GetBValue(color1)-GetBValue(color2));
	return (r + g + b)/3/255;
}

class DNA{
public:
	Triangle* genes;
	Image* my_img;

	DNA(){
		genes = new Triangle[AMOUNT];
		my_img = NULL;
	}
	
	DNA(Triangle* newgenes){
		genes = newgenes;
		my_img = NULL;
	}
	
	~DNA(){
		delete[] genes;
		if (my_img)
			delete my_img;
	}
	
	DNA* crossover(DNA* partner){
		Triangle* newgenes = new Triangle[AMOUNT];
		int mid = AMOUNT/2;
		for (int i=0;i<AMOUNT;i++){
			if (i > mid){
				newgenes[i] = genes[i];
			} else {
				newgenes[i] = partner->genes[i];
			}
		}
		return new DNA(newgenes);
	}
	
	double calaFitness(){
		double sum = 0;
		for (int i=0;i<img->width;i++){
			for (int j=0;j<img->height;j++){
				sum += color_dist(my_img->get(i,j),img->get(i,j));
			}
		}
		sum /= my_img->width*my_img->height;
		delete my_img;
		my_img = NULL;
		return sum;
	}
	
	void mutation(){
		for (int i=0;i<AMOUNT;i++){
			if (RandomF(1) < MUTATION_RATE){
				genes[i] = Triangle();
			}
		}
	}
	
	void show(){
		my_img = new Image(img->width, img->height, 3);
		for (int i=0;i<AMOUNT;i++){
			genes[i].show(my_img);
		}
		drawImage(my_img);
	}
};