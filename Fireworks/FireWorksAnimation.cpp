#include "Firework.h"
#include "Maths.h"
#include <ctime>
#include <string>

COLORREF HSVToRGB(int hue, char saturation, char brightness) {
	double r = 0, g = 0, b = 0;

	if (saturation == 0)
	{
		r = brightness;
		g = brightness;
		b = brightness;
	}
	else
	{
		int i;
		double f, p, q, t;

		if (hue == 360)
			hue = 0;
		else
			hue = hue / 60;

		i = (int)trunc(hue);
		f = hue - i;

		p = brightness * (1.0 - saturation);
		q = brightness * (1.0 - (saturation * f));
		t = brightness * (1.0 - (saturation * (1.0 - f)));

		switch (i)
		{
		case 0:
			r = brightness;
			g = t;
			b = p;
			break;

		case 1:
			r = q;
			g = brightness;
			b = p;
			break;

		case 2:
			r = p;
			g = brightness;
			b = t;
			break;

		case 3:
			r = p;
			g = q;
			b = brightness;
			break;

		case 4:
			r = t;
			g = p;
			b = brightness;
			break;

		default:
			r = brightness;
			g = p;
			b = q;
			break;
		}

	}

	return RGB((unsigned char)(r * 255), (unsigned char)(g * 255), (unsigned char)(b * 255));
}

vector<Firework*> fireworks;
clock_t timer;

void setup(){
	srand(time(NULL));
	stroke(RGB(0,0,0));
	height/=2;
	timer = clock();
}

void draw(){
	background();
	alpha(30);
	if (RandomF(1) < 0.03){
		fireworks.push_back(new Firework(HSVToRGB(RandomF(360),1,1)));
	}
	for (vector<Firework*>::iterator it = fireworks.begin() ; it != fireworks.end();){
		(*it)->update();
		(*it)->show();
		if ((*it)->dead()){
			delete *it;
			it = fireworks.erase(it);
		}else{
			++it;
		}
	}
	fill();
	string passed = to_string(frameCount/((float)(clock() - timer)/CLOCKS_PER_SEC));
	drawText(0,0,passed.c_str(),passed.length());
	Sleep(10);
}