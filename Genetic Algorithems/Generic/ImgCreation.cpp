#include "Graph\Graph.h"
#include "Population.h"
#include "Keyboard.h"
#include <ctime>
#include <string>

Image* originalImg;
Population** pop;
short groups = 3;
Graph* g;
int generation = 0;
const char* names[3] = {"square", "triangle", "circle"};
const char* file_name = "halfs";
const char* path = "Imgs/";
int max_size = 0;

bool dirExists(const char* dirName_in){
  DWORD ftyp = GetFileAttributesA(dirName_in);
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}

void createDirs(){
	if (!dirExists(path)){
		CreateDirectoryA(path, NULL);
	}
	// string temp = string(path) + string(file_name);
	// const char* file_path = temp.c_str();
	// if (!dirExists(file_path)){
		// CreateDirectoryA(file_path, NULL);
	// }
}

void initGraph() {
	g = new Graph(groups, 500, 250, 50, 50+((groups-1)/(width / originalImg->width)+1)*originalImg->height);
	//g->setMode(Graph::LINES);
	g->setGensLimit(20);
	vector<Point> vec;
	for (int i = 0; i < groups; i++)
		vec.push_back(Point(0, 0));
	g->addGen(vec);
}

void keyboardInput(){
	if (isFocused()){
		int key = keysDown();					   
		switch(key){
			case 80:
				while(keysDown()!=80);
				break;
			case 83:
				for (short j = 0; j < groups; j++)
					pop[j]->saveBest(path, file_name, names[j]);
				break;
		}
	}
}

void drawInfo(short index){
	g->show();
	fill(RGB(255,100, 255));
	int y_offset = 50 + ((groups - 1) / (width / originalImg->width) + 1)*originalImg->height;
	string passed = "gen: "+to_string(generation);
	drawText(560, y_offset,passed.c_str(),passed.length());
	passed = "index: "+to_string(index);
	drawText(560, y_offset+20,passed.c_str(),passed.length());
	for (short j = 0; j < groups; j++) {
		passed = "best_"+ string(names[j]) +": " + to_string(pop[j]->bestFitness);
		drawText(560, y_offset + 40 + 20*j, passed.c_str(), passed.length());
	}
}

void setup(){
	createCanvas();
	srand((unsigned int)time(NULL));
	noStroke();
	createDirs();
	originalImg = loadImage((string(path)+"src/"+string(file_name)+".bmp").c_str());
	pop = new Population*[groups];
	for (short j = 0; j < groups; j++) {
		pop[j] = new Population(j, 200, 5, (ElementType)j, 0.01f);
		if (pop[j]->size > max_size)
			max_size = pop[j]->size;
	}
	initGraph();
}

void draw(){
	background();
	keyboardInput();
	short index = (short)((frameCount-1)%max_size);
	vector<Point> vec;
	for (short j = 0; j < groups; j++) {
		pop[j]->run(index);
		if(index < pop[j]->size)
			pop[j]->evaluate(index);
		if (index == pop[j]->size - 1) {
			//vec.push_back(Point(generation, pop[j]->maxFitness * 100));
			vec.push_back(Point(generation, pop[j]->avgFitness * 100));
			pop[j]->evaluate();
			pop[j]->selection();
		}
	}
	drawInfo(index);
	if (index == max_size - 1) {
		generation++;
		g->addGen(vec);
	}
}