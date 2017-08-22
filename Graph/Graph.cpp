#include "Graphics.cpp"
#include <vector>
#include <string>

class Graph{
	int width;
	int height;
	int xOffset;
	int yOffset;
	int n;
	vector<Point>* lines;
public:
	Point* max;
	Point* min;
	Graph(int n, int width,int height, int xOffset = 0, int yOffset = 0){
		this->n  = n;
		this->lines = new vector<Point>[this->n];
		this->width  = width;
		this->height = height;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->max = NULL;
		this->min = NULL;
		
	}
	
	void addGen(vector<Point> points){
		if (points.size() > 0){
			if(min == NULL)
				this->min = new Point(points.front().x,points.front().y);
			if(max == NULL)
				this->max = new Point(points.front().x,points.front().y);
			int i;
			vector<Point>::iterator it;
			for(it = points.begin(), i = 0; it != points.end(); ++it, ++i) {
				lines[i].push_back(*it);
				if (it->y > this->max->y)
					this->max->y = it->y;
				if (it->y < this->min->y)
					this->min->y = it->y;
				if (it->x > max->x)
					this->max->x = it->x;
				if (it->x < min->x)
					this->min->x =it->x;
			}
		}
	}
	
	void show(){
		float xScale = (this->max->x-this->min->x)/this->width;
		float yScale = (this->max->y-this->min->y)/this->height;
		float minX = this->min->x/xScale,minY = this->min->y/yScale;
		float maxX = this->max->x/xScale,maxY = this->max->y/yScale;
		
		noFill();
		stroke(RGB(100,100,100));
		string val;
		for(float i = 0; i < this->height; i+= this->height/10){
			drawLine(this->xOffset,this->yOffset+i,this->width+this->xOffset,this->yOffset+i);
			val = to_string((int)((this->max->y - yScale*i) * 100)/100);
			drawText(this->xOffset - 30, this->yOffset+i-10,val.c_str(),val.length());
		}
		drawRectangle(this->xOffset,this->yOffset,this->width,this->height);
		val = to_string((int)(this->min->y * 100)/100);
		drawText(this->xOffset - 30, this->yOffset+this->height-10,val.c_str(),val.length());
			
		
		stroke(RGB(255,255,255));
		if (minY*maxY < 0)
			drawLine(this->xOffset,this->yOffset+this->height+minY,this->width+this->xOffset,this->yOffset+this->height+minY);
		if (minX*maxX < 0)
			drawLine(this->xOffset-minX,this->yOffset,this->xOffset-minX,this->height+this->yOffset);
			
		for(int i = 0; i < n; ++i) {
			beginShape();
			fill(rainbowColors(i*2));
			for(vector<Point>::iterator it = lines[i].begin(); it != lines[i].end(); ++it) {
				float x = it->x/xScale-minX+this->xOffset;
				float y = this->yOffset+this->height - (it->y/yScale-minY);
				vertex(Point(x,y));
			}
		}
	}
};