#include "Population.cpp"
#include "Keyboard.cpp"
#include <ctime>

Population* pop;

void setup(){
	srand(time(NULL));
	myfile.open("log.txt");
	img = loadImage("halfs.bmp");
	bestImg = NULL;
	pop = new Population();
}

void draw(){
	if (GetForegroundWindow() == myconsole){
		int key = keysDown();
		switch(key){
			case 80:
				while(keysDown()!=80);
				break;
			case 83:
				string passed = "fitness_"+to_string(bestFitness)+".bmp";
				SaveBMP(bestImg,passed.c_str());
				break;
		}
	}
	short index = (frameCount-1)%POP_SIZE;
	pop->run(index);
	pop->evaluate(index);
	if (index == POP_SIZE - 1){
		pop->evaluate();
		pop->selection();
	}
	fill(RGB(255,0,0));
	string passed = "gen: "+to_string(pop->generation);
	drawText(img->width+10,0,passed.c_str(),passed.length());
	passed = "index: "+to_string(index);
	drawText(img->width+10,20,passed.c_str(),passed.length());
	passed = "best: "+to_string(bestFitness);
	drawText(img->width+10,40,passed.c_str(),passed.length());
}