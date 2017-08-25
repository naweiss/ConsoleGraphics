#include "Population.cpp"
#include "Keyboard.cpp"
#include <ctime>
#include <string>

Population* pop;
int sleep_time;

void setup(){
	srand(time(NULL));
	width /=2;
	height /= 2;
	sleep_time = 0;
	myfile.open ("log.txt");
	pop = new Population();
	target = Vector(width/2, 50);
	fill();
}

void draw(){
	if (GetForegroundWindow() == myconsole){
		int key = keysDown();
		if(key == 80)
			while(keysDown()!=80);
		else{
			if(isKeyDown(188))
				sleep_time++;
			if(isKeyDown(190))
				sleep_time--;
		}
	}
	background();
	pop->run();
	n++;
	if (sleep_time < 0){
		for(int i = abs(sleep_time); i > 0 && n < lifespan; i--){
			background();
			pop->run();
			n++;
		}
	}
	if (n == lifespan){
		n = 0;
		pop->evaluate();
		pop->selection();
	}
	drawRectangle(rx, ry, rw, rh);
	drawEllipse(target.x,target.y,8,8);
	
	string passed = to_string(n);
	drawText(width - 50,20,passed.c_str(),passed.length());
	passed = "slow: "+to_string(sleep_time);
	drawText(width - 60,0,passed.c_str(),passed.length());
	
	if (sleep_time > 0)
		Sleep(sleep_time);
}