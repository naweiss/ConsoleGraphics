#include "Graphics.cpp"
#include "Keyboard.cpp"
#include <string>

Image* img;

void setup(){
	img = loadImage("halfs.bmp");
}

void draw(){
	if (GetForegroundWindow() == myconsole){
		int key = keysDown();
		switch(key){
			case 80:
				noLoop();
				break;
		}
	}
	drawImage(img);
}