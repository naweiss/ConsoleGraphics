#include "Population.cpp"
#include "Keyboard.cpp"
#include <ctime>

// COLORREF color_gray_scale(COLORREF color){
	// //Gray-Scale color: 0.21 R + 0.72 G + 0.07 B.
	// short bright= GetRValue(color)*0.21+GetGValue(color)*0.72+GetBValue(color)*0.07;
	// return RGB(bright,bright,bright);
// }

// void image_gray_scale(Image* image){
	// for(int i=0;i<image->width;i++)
		// for(int j=0;j<image->height;j++)
			// image->set(i,j,color_gray_scale(image->get(i,j)));
// }

Population* pop;

void setup(){
	srand(time(NULL));
	myfile.open("log.txt");
	img = loadImage("halfs.bmp");
	// image_gray_scale(img);
	// SaveBMP(img,"gs_halfs.bmp");
	width = img->width;
	height = img->height;
	pop = new Population();
}

void draw(){
	if (GetForegroundWindow() == myconsole){
		int key = keysDown();
		switch(key){
			case 80:
				while(keysDown()!=80);
				break;
			case 83:
				string passed = "finess_"+to_string(bestFitness)+".bmp";
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
	fill(RGB(255,0,0));
	string passed = "gen: "+to_string(pop->generation);
	drawText(0,0,passed.c_str(),passed.length());
	passed = "index: "+to_string(index);
	drawText(0,20,passed.c_str(),passed.length());
	passed = "best: "+to_string(bestFitness);
	drawText(0,40,passed.c_str(),passed.length());
}