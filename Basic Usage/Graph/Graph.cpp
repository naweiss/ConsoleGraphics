#include "Graph.h"
#include <string>

Graph::Graph(int n, int width,int height, int xOffset, int yOffset){
	this->n  = n;
	this->lines = new vector<Point>[this->n];
	this->width  = width;
	this->height = height;
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->max = NULL;
	this->min = NULL;
	this->limit = 0;
	this->type = Graph::DOTED_LINES;
	
}

void Graph::setMode(Graph::Type type){
	this->type = type;
}

void Graph::setGensLimit(int limit){
	if (limit > 0)
		this->limit = limit;
}

void Graph::addGen(vector<Point> points){
	if (points.size() > 0){
		if(this->limit == 0){
			if(min == NULL)
				this->min = new Point(points.front().x,points.front().y);
			if(max == NULL)
				this->max = new Point(points.front().x,points.front().y);
		}
		int len = lines[0].size(), i;
		vector<Point>::iterator it;
		for(it = points.begin(), i = 0;
			it != points.end();
			++it, ++i) {
			lines[i].push_back(*it);
			if(this->limit > 0){
				if (len > this->limit)
					lines[i].erase(lines[i].begin());
			} else {
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
}

void Graph::show(){
	if (this->limit > 0)
		this->calc();
	float xScale = (this->max->x-this->min->x)/this->width;
	float yScale = (this->max->y-this->min->y)/this->height;
	float minX = this->min->x/xScale,minY = this->min->y/yScale;
	float maxX = this->max->x/xScale,maxY = this->max->y/yScale;
	
	noFill();
	stroke(RGB(100,100,100));
	string val;
	for(float i = 0; i < this->height; i+= this->height/10){
		drawLine(this->xOffset,
				 this->yOffset+i,
				 this->width+this->xOffset,
				 this->yOffset+i);
		val = to_string((int)((this->max->y - yScale*i) * 100)/100);
		drawText(this->xOffset - 30, 
				 this->yOffset+i-10,
				 val.c_str(),
				 val.length());
	}
	drawRectangle(this->xOffset,
				  this->yOffset,
				  this->width,
				  this->height);
	val = to_string((int)(this->min->y * 100)/100);
	drawText(this->xOffset - 30,
			 this->yOffset+this->height-10,
			 val.c_str(),
			 val.length());
	
	stroke(RGB(255,255,255));
	if (minY*maxY < 0)
		drawLine(this->xOffset,this->yOffset+this->height+minY,this->width+this->xOffset,this->yOffset+this->height+minY);
	if (minX*maxX < 0)
		drawLine(this->xOffset-minX,this->yOffset,this->xOffset-minX,this->height+this->yOffset);

	for(int i = 0; i < n; ++i) {
		if (type != Graph::DOTS)
			beginShape();
		fill(rainbowColors(i*2));
		for(vector<Point>::iterator it = lines[i].begin();
			it != lines[i].end();
			++it) {
			float x = it->x/xScale-minX+this->xOffset;
			float y = this->yOffset+this->height - (it->y/yScale-minY);
			if (type != Graph::DOTS)
				vertex(Point(x,y));
			if (type != Graph::LINES)
				drawCircle(x,y,3);
		}
	}
}

void Graph::calc(){
	this->min = new Point(lines[0].front().x,lines[0].front().y);
	this->max = new Point(lines[0].front().x,lines[0].front().y);
	for(int i = 1; i < n; ++i) {
		for(vector<Point>::iterator it = lines[i].begin(); 
			it != lines[i].end();
			++it) {
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