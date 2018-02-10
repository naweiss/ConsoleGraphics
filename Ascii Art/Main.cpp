#include "CharPool.h"
#include "Graphics.h"
#include "Keyboard.h"
#include <iostream>
#define TEXT_SIZE 10
#define SAVE_TO_FILE
using namespace std;

CharPool pool;
int x = 0, y = 0,
	w = -1, h = -1;
double best_score = 0;
char best_char;
Image* img;

#ifdef SAVE_TO_FILE

#include <vector>
#include <fstream>

vector<char>::iterator it;
vector<char> chars_data;
ofstream myfile;
void save(){
	myfile.open("data.txt");
	int x = 0, y = 0;
	for(it = chars_data.begin(); it != chars_data.end(); it++){
		char c = *it;
		myfile << c;
	}
	myfile.close();
}
#endif

void keyboardInput(){
	if (isFocused()){
		int key = keysDown();
		if(key == 83){
			SaveBMP(GetCanvas(width,height),"ans.bmp");
		}		
	}
}

double color_dist(COLORREF color1,COLORREF color2){
	double r = pow((GetRValue(color1)-GetRValue(color2))/255,2.0);
	double g = pow((GetGValue(color1)-GetGValue(color2))/255,2.0);
	double b = pow((GetBValue(color1)-GetBValue(color2))/255,2.0);
	return (r + g + b)/3;
}

double calaScore(){
	Image* canvas = GetCanvas(x+w,y+h,x,y);
	double sum = 0;
	for (int i=0;i<w;i++){
		for (int j=0;j<h;j++){
			sum += color_dist(canvas->get(i,j),img->get(x+i,y+j));
		}
	}
	delete canvas;
	return 1 - (sum / (w*h));
}

void drawChar(char c){
	if(w != -1 && h != -1){
		fill(RGB(255,255,255));
		drawRectangle(x,y,w,h);
	}
	fill(RGB(0,0,0));
	drawText(x,y,&c,1);
	Point size = getTextSize(&best_char,1);
	w = size.x;
	h = size.y;
}

void nextCell(){
	#ifdef SAVE_TO_FILE
	chars_data.push_back(best_char);
	#endif
	Point size = getTextSize(&best_char,1);
	x += size.x;
	if (x >= width){
		x = 0;
		y += size.y;
		#ifdef SAVE_TO_FILE
		chars_data.push_back('\n');
		#endif
	}
	if(y >= height){
		#ifdef SAVE_TO_FILE
		save();
		#endif
		SaveBMP(GetCanvas(width,height),"ans.bmp");
		noLoop();
	}
}

void setup(){
	img = loadImage("test.bmp");
	createCanvas(img->width,img->height);
	background(RGB(255,255,255));
	textSize(TEXT_SIZE);
	noStroke();
}

void draw(){
	keyboardInput();
	if(pool.isDone()){
		drawChar(best_char);
		nextCell();
		best_score = 0;
		w = h = -1;
		pool.restart();
	}
	char c = pool.next();
	drawChar(c);
	double score = calaScore();
	if(score > best_score){
		best_score = score;
		best_char = c;
	}
}