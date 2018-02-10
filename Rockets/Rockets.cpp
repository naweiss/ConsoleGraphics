#include "Population.h"
#include "Keyboard.h"
#include "Graph.h"
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

Population** pop;
Graph* g;
short groups = 7;
int gen = 1;
int sleep_time;

bool dirExists(const char* dirName_in){
  DWORD ftyp = GetFileAttributesA(dirName_in);
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}

void keyboardInput(){
	if (isFocused()){
		int key = keysDown();
		if(key == 80)
			while(keysDown()!=80);
		else {
			if(key == 83){
				string name = "Imgs\\graph_"+to_string(gen)+".bmp";
				SaveBMP(GetCanvas(width/2+600,350,width/2,0),name.c_str());
			}
			else{
				if(isKeyDown(188))
					sleep_time++;
				if(isKeyDown(190))
					sleep_time--;
			}
		}
		
	}
}

void globals(){
	g->show();
	fill();
	drawRectangle(rx, ry, rw, rh);
	drawEllipse(target.x,target.y,8,8);
	
	string passed = to_string(n);
	drawText(width/2 - 50,20,passed.c_str(),passed.length());
	passed = "slow: "+to_string(sleep_time);
	drawText(width/2 - 60,0,passed.c_str(),passed.length());
	
	if (sleep_time > 0)
		Sleep(sleep_time);
}

void popRun(){
	for(short j = 0; j < groups; j++)
		pop[j]->run();
	n++;
	if (sleep_time < 0){
		for(int i = abs(sleep_time); i > 0 && n < lifespan; i--, n++){
			background();
			for(short j = 0; j < groups; j++)
				pop[j]->run();
		}
	}
}

void initGraph(){
	g = new Graph(groups,500,250,50+width/2,50);
	g->setMode(Graph::LINES);
	g->setGensLimit(30);
	vector<Point> vec;
	for (int i = 0; i < groups; i++)
			vec.push_back(Point(0,0));
	g->addGen(vec);
}

void setup(){
	srand(time(NULL));
	sleep_time = 0;
	if (!dirExists("Logs")){
		CreateDirectory("Logs", NULL);
	}
	if (!dirExists("Imgs")){
		CreateDirectory("Imgs", NULL);
	}
	pop = new Population*[groups];
	for(short j = 0; j < groups; j++)
		pop[j] = new Population(j,pow(j+1,2)*0.05/100);
	target = Vector(width/4, 50);
	initGraph();
	fill();
}

void draw(){
	background();
	popRun();
	if (n == lifespan){
		n = 0;
		vector<Point> vec;
		for(short j = 0; j < groups; j++){
			double avgFit = pop[j]->evaluate();
			vec.push_back(Point(gen,avgFit*100));
			pop[j]->selection();
		}
		g->addGen(vec);
		gen++;
	}
	globals();
	keyboardInput();
}