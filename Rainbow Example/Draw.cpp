#include "Graphics.cpp"

void setup(){
	
}

void draw(){
	Sleep(100);
	short rect_size = 30, grid_size = 15 ,border = 20;
	for (int i = 0; i < grid_size*2; i++)
	{
		for (int j = 0;j < grid_size; j++)
		{
			fill(rainbowColors(i+j));
			drawRectangle(border+i*rect_size,border+j*rect_size,rect_size,rect_size);
		}
	}
	noLoop();
}