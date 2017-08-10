#include "Population.cpp"
#include "Keyboard.cpp"
#include <ctime>

Population* pop;
int sleep_time;

void setup(){
	srand(time(NULL));
	myfile.open ("halfs.txt");
	width = height = 350;
	sleep_time = 0;
	img = loadImage("frog.bmp");
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
	if (index == POP_SIZE - 1){
		pop->evaluate();
		pop->selection();
	}
	
	fill();
	string passed = "index: "+to_string(index);
	drawText(width - 60,0,passed.c_str(),passed.length());
}