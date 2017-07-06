#include "Graphics.cpp"
#include "Keyboard.cpp"
#include <string>

static int lvl_x;
static int lvl_y;

void setup(){
	lvl_x = 0;
	height /= 2;
	width /= 2;
}

void draw(){
	int key = KeyDown();
	if (key != -1){
		string str = to_string(key);
		drawText(lvl_y*30,lvl_x*18,str.c_str(),str.length());
		lvl_x++;
	}
	if (lvl_x*18 > height){
		lvl_x = 0;
		lvl_y++;
	}
	if (lvl_y*30 > width){
		lvl_y = lvl_x = 0;
		background();
	}
}