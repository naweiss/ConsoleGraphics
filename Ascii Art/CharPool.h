#include "Graphics.h"
#define POOL_SIZE 95
#include <iostream>
using namespace std;

Image* Latter(int code){
	background(RGB(255,255,255));
	char c = (char)code;
	drawText(0,0,&c,1);
	Point size = getTextSize(&c,1);
	return GetCanvas(size.x,size.y);
}

class CharPool{
	Image* pool[POOL_SIZE];
	int pool_index;
public:
	CharPool(){
		pool_index = 0;
		for (int i = 32, count = 0; i < 127; i++){
			pool[count++] = Latter(i);
		}
	}
	
	~CharPool(){
		for (int i = 0; i < POOL_SIZE; i++)
			delete pool[i];
	}
	
	bool isDone(){
		return pool_index == POOL_SIZE;
	}
	
	Image* next(){
		return pool[pool_index++];
	}
};