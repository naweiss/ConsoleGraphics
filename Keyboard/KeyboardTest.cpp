#include "Graphics.cpp"
#include "Keyboard.cpp"
#include <string>

static int lvl_y;
static int lvl_x;
static int col;

void setup(){
	lvl_y = lvl_x = col = 0;
	height /= 2;
	width /= 2;
}

void draw(){
	int key = keysDown();
	if (key != -1){
		fill(rainbowColors(col/1000.0));
		string str = to_string(key);
		drawText(lvl_x*30,lvl_y*18,str.c_str(),str.length());
		lvl_y++;
	}
	if ((lvl_y+1)*18 > height){
		lvl_y = 0;
		lvl_x++;
	}
	if ((lvl_x+1)*30 > width){
		lvl_y = lvl_x = 0;
		background();
	}
	col++;
}