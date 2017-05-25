#include "Graphics.cpp"
#include <vector>
#include <ctime>

class Circle{
public:
	float r;
	float x;
	float y;
	COLORREF c;
	bool growing;
	Circle(float x, float y,COLORREF c){
		this->x = x;
		this->y = y;
		this->c = c;
		this->r = 1;
		this->growing = true;
	}
	
	void grow(){
		if (growing)
			this->r++;
	}
	
	bool edges(){
		return (x+r > width || y+r > height || x-r < 0 || y-r < 0);
	}
	
	void show(){
		fill(this->c);
		drawCircle(this->x,this->y,this->r);
	}
};

static vector<Circle> circles;
static Image* img = NULL;

void setup(){
	srand(time(NULL));
	noStroke();
	img = loadImage("kitten.bmp");
	if (img == NULL){
		noLoop();
		return;
	}
	width = img->width;
	height = img-> height;
}

double dist(int x0, int y0, int x1, int y1){
	return sqrt(pow(abs(x0-x1),2)+pow(abs(y0-y1),2));
}

bool newCircle(){
	int x = Random(width);
	int y = Random(height);
	
	for (vector<Circle>::iterator c=circles.begin(); c != circles.end(); ++c){
		if (dist(c->x,c->y,x,y) <= c->r)
			return false;
	}
	int index = x+y*width;
	circles.push_back(Circle(x,y,img->pixels[index]));
	return true;
}

void draw(){
	background();
	for (vector<Circle>::iterator c=circles.begin(); c != circles.end(); ++c){
		if (c->growing){
			if (c->edges()){
				c->growing = false;
			} else {
				for (vector<Circle>::iterator other=circles.begin(); other != circles.end(); ++other){
					if (other == c)
						continue;
					if (dist(c->x,c->y,other->x,other->y) - 1<= c->r + other->r){
						c->growing = false;
						break;
					}
				}
			}
		}
		c->show();
		c->grow();
	}
	
	int total = 100;
	int count = 0;
	int atempts = 0;
	
	while(count < total){
		if (newCircle()){
			count++;
		}
		atempts++;
		if (atempts > total*10){
			noLoop();
		}
	}
}