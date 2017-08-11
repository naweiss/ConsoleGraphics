#include "Population.cpp"
#include "Keyboard.cpp"
#include <ctime>

Population* pop;

void setup(){
	srand(time(NULL));
	myfile.open ("log.txt");
	img = loadImage("halfs_2.bmp");
	width = img->width;
	height = img->height;
	pop = new Population();
}

void draw(){
	int key = keysDown();
	switch(key){
		case 80:
			while(keysDown()!=80);
			break;
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
	drawText(width - 60,0,passed.c_str(),passed.length());
	passed = "index: "+to_string(index);
	drawText(width - 70,20,passed.c_str(),passed.length());
	passed = "best: "+to_string(bestFitness);
	drawText(width - 100,40,passed.c_str(),passed.length());
}