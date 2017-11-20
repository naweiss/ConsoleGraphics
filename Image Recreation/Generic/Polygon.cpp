#include "Population.h"
#include "Keyboard.h"
#include <ctime>
#include <string>

Population* pop;
const char* file_name = "halfs";

bool dirExists(const char* dirName_in){
  DWORD ftyp = GetFileAttributesA(dirName_in);
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}

void createDirs(){
	if (!dirExists("Logs")){
		CreateDirectory("Logs", NULL);
	}
	if (!dirExists("Imgs")){
		CreateDirectory("Imgs", NULL);
	}
	if (!dirExists(("Imgs/"+string(file_name)).c_str())){
		CreateDirectory(("Imgs/"+string(file_name)).c_str(), NULL);
	}
}

void keyboardInput(){
	if (isFocused()){
		int key = keysDown();					   
		switch(key){
			case 80:
				while(keysDown()!=80);
				break;
			case 83:
				string passed = "Imgs/"+string(file_name)+"/fitness_"+to_string(pop->bestFitness)+".bmp";
				SaveBMP(pop->bestImg,passed.c_str());
				break;
		}
	}
}

void drawInfo(short index){
	fill(RGB(255,0,0));
	string passed = "gen: "+to_string(pop->generation);
	drawText(img->width+10,0,passed.c_str(),passed.length());
	passed = "index: "+to_string(index);
	drawText(img->width+10,20,passed.c_str(),passed.length());
	passed = "best: "+to_string(pop->bestFitness);
	drawText(img->width+10,40,passed.c_str(),passed.length());
}

void setup(){
	srand(time(NULL));
	noStroke();
	img = loadImage(("Imgs/src/"+string(file_name)+".bmp").c_str());
	pop = new Population(1,0.01);
}

void draw(){
	keyboardInput();
	short index = (frameCount-1)%Population::POP_SIZE;
	pop->run(index);
	pop->evaluate(index);
	if (index == Population::POP_SIZE - 1){
		pop->evaluate();
		pop->selection();
	}
	drawInfo(index);
}