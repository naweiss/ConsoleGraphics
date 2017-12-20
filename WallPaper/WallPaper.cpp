#include "Serializer.cpp"

const short SLEEP = 25;
vector<Image*>* imgs;
vector<Image*>::iterator it;
int x_off, y_off;

void setup(){
    Info inf;
    Serializer s;
    imgs = s.deserialize(inf);
    x_off = width - inf.width;
    y_off = height - inf.height;
    it = imgs->begin();
}

void draw(){
    if(it == imgs->end())
        it = imgs->begin();
    drawImage(*(it++),x_off,y_off);
    Sleep(SLEEP);
}