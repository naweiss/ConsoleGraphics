#include "Graphics.cpp"
#include <ctime>

class Symbol{
private:
	int x;
	int y;
	int speed;
	int switchInterval;
	WCHAR value[2];
public:
	bool first;
	Symbol(int x = 0,int y = 0,int speed = 0, bool first = false){
		this->x = x;
		this->y = y;
		this->speed = speed;
		this->first = first;
		this->switchInterval = Random(2,20);
	}
	
	void setToRandomSymbol(){
		int charType = Random(0, 8);
		if (frameCount%switchInterval == 0){
			if (charType > 1) {
				value[0]= 0x30A0+Random(96);
				
			}
			else{
				value[0] = '0'+Random(0,10);
			}
			value[1]= 0x0000;
		}
	}
	
	void render(){
		if (this->x > 0 && this-> y > 0){
			drawText(this->x,this->y,this->value,1);
		}
		this->setToRandomSymbol();
		this->rain();
	}
	
	void rain(){
		if (this->y >= height)
			this->y =0;
		else
			this->y += this->speed;
	}
};

static int symbolSize = 14;

class Stream{
private:
	Symbol* symbols;
	int speed;
	int totalSymbols;
public:
	Stream(){
		this->totalSymbols = Random(5,35);
		this->speed = Random(5,20);
		symbols = new Symbol[this->totalSymbols];
	}
	
	~Stream(){
		delete[] symbols;
	}
	
	void generateSymbols(int x, int y){
		bool first = (Random(0,3) == 1);
		for(int i=0; i < totalSymbols; i++){
			symbols[i] = Symbol(x,y,this->speed, first);
			symbols[i].setToRandomSymbol();
			y -= symbolSize;
			first = false;
		}
	}
	
	void render(){
		for(int i=0; i < totalSymbols; i++){
			if (symbols[i].first)
				fill(RGB(180,255,180));
			else
				fill(RGB(0,255,70));
			symbols[i].render();
		}
	}
};

static Stream** streams;

void setup(){
	srand (time(NULL));
	streams = new Stream*[width/symbolSize];
	int x =0;
	for (int i=0;i <= width/symbolSize; i++)
	{
		streams[i] = new Stream();
		streams[i]->generateSymbols(x, -Random(0,1000));
		x += symbolSize;
	}
	textSize(symbolSize);
}

void draw(){
	background(RGB(0,0,0),150);
	//background();
	for (int i=0;i <= width/symbolSize; i++)
	{
		streams[i]->render();
	}
}