#include "Graphics.cpp"
#include "Math.cpp"

const float MUTATION_RATE = 0.02;
Image* img;

class DNA{
public:
	BYTE* genes;
	int size;

	DNA(){
		size = img->width*img->height;
		genes = new BYTE[size];
		for(long i=0;i<size;i++){
			genes[i] = Random(2) == 1 ? 255 : 0;
		}
	}
	
	~DNA(){
		delete[] genes;
	}
	
	DNA* crossover(DNA* partner){
		DNA* new_dna = new DNA;
		for (int i=0;i<size;i++){
			if (genes[i] == partner->genes[i])
				new_dna->genes[i] = genes[i];
			new_dna->genes[i] = Random(2) == 1 ? 255 : 0;
		}
		return new_dna;
	}
	
	void mutation(){
		for (int i=0;i<size;i++){
			if (RandomF(1) < MUTATION_RATE){
				genes[i] = Random(2) == 1 ? 255 : 0;
			}
		}
	}
	
	double dist(){
		double sum = 0;
		for(long i=0;i<size;i++){
			sum += abs(img->pixels[i*img->Bpp]-genes[i]);
		}
		return pow(size - sum/255,4)/pow(size,4);
	}
	
	void show(){
		for(int i=0;i<img->width;i++){
			for(int j=0;j<img->height;j++){
				int index = (i*img->width)+j;
				fill(RGB(genes[index],genes[index],genes[index]));
				SetPixelC(i,j);
			}
		}
	}
};