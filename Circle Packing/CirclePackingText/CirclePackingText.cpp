#include "Graphics.cpp"
#include <vector>
#include <ctime>

class Circle{
private:
public:
	float r;
	float x;
	float y;
	bool growing;
	Circle(float x, float y){
		this->x = x;
		this->y = y;
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
		drawCircle(this->x,this->y,this->r);
	}
};

static vector<Circle> circles;
static vector<Point> spots;
static Image* img = NULL;

void setup(){
	srand(time(NULL));
	stroke();
	noFill();
	img = loadImage("2017.bmp");
	if (img == NULL){
		noLoop();
		return;
	}
	width = img->width;
	height = img-> height;
	int count = 0;
	for (int x=0;x<img->width;x+=2){
		for (int y=0;y<img->height;y+=2){
			int index = x+y*img->width;
			if (GetRValue(img->pixels[index]) > 0
				|| GetGValue(img->pixels[index]) > 0
				|| GetBValue(img->pixels[index]) > 0){
				spots.push_back(Point(x,y));
			}
		}		
	}
}

double dist(int x0, int y0, int x1, int y1){
	return sqrt(pow(abs(x0-x1),2)+pow(abs(y0-y1),2));
}

bool newCircle(){
	unsigned int index = Random(spots.size());
	int x = spots[index].x;
	int y = spots[index].y;
	
	for (vector<Circle>::iterator c=circles.begin(); c != circles.end(); ++c){
		if (dist(c->x,c->y,x,y) <= c->r)
			return false;
	}
	circles.push_back(Circle(x,y));
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
					if (dist(c->x,c->y,other->x,other->y) <= c->r + other->r){
						c->growing = false;
						break;
					}
				}
			}
		}
		c->show();
		c->grow();
	}
	
	int total = 40;
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