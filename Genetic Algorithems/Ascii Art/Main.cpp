#include "Population.h"
#include "Keyboard.h"
#include <string>
#include <ctime>

Population* pop;
const char* file_name = "test";

bool dirExists(const char* dirName_in){
  DWORD ftyp = GetFileAttributesA(dirName_in);
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}								 

void setup(){
	srand (time(NULL));
	fill(RGB(0,0,0));	
	textSize(SYMBOL_SIZE);
	if (!dirExists("Logs")){
		CreateDirectory("Logs", NULL);
	}
	if (!dirExists("Imgs")){
		CreateDirectory("Imgs", NULL);
	}
	myfile.open(("Logs/log_"+string(file_name)+".txt").c_str());
	img = loadImage(("Imgs/"+string(file_name)+".bmp").c_str());
	bestImg = NULL;			
	pop = new Population();
}

void draw(){
	if (isFocused()){
		int key = keysDown();					   
		switch(key){
			case 80:
				while(keysDown()!=80);
				break;
			case 83:
				string passed = "Imgs/fitness_"+string(file_name)+"_"+to_string(bestFitness)+".bmp";
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
	string passed = "gen: "+to_string(pop->generation);
	drawText(OFFSET,HEIGHT+OFFSET,passed.c_str(),passed.length());
	passed = "index: "+to_string(index);
	drawText(OFFSET,HEIGHT+OFFSET*2,passed.c_str(),passed.length());
	passed = "best: "+to_string(bestFitness);
	drawText(OFFSET,HEIGHT+OFFSET*3,passed.c_str(),passed.length());
}