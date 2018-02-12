#include "CharPool.h"

class CharImage{
	Image* img;
	CharPool* pool;
	Image*** bestChars;
	double** bestScore;
	int w;
	int h;
	
	static double color_dist(COLORREF color1,COLORREF color2){
		double r = pow((GetRValue(color1)-GetRValue(color2))/255,2.0);
		double g = pow((GetGValue(color1)-GetGValue(color2))/255,2.0);
		double b = pow((GetBValue(color1)-GetBValue(color2))/255,2.0);
		return (r + g + b)/3;
	}
public:
	CharImage(Image* img){
		this->img = img;
		this->pool = new CharPool();
		char dummy = ' ';
		Point size = getTextSize(&dummy,1);
		this->w = size.x;
		this->h = size.y;
		this->bestChars = new Image**[(width+w-1)/w];
		this->bestScore = new double*[(width+w-1)/w];
		for(int i=0;i<(width+w-1)/w;i++)
			bestChars[i] = new Image*[(height+h-1)/h];
		for(int i=0;i<(width+w-1)/w;i++){
			bestScore[i] = new double[(height+h-1)/h];
			for(int j=0;j<(height+h-1)/h;j++)
				bestScore[i][j] = 0;
		}
	}
	
	~CharImage(){
		delete pool;
		for(int i=0;i<(width+w-1)/w;i++)
			delete[] bestChars[i];
		for(int i=0;i<(width+w-1)/w;i++)
			delete[] bestScore[i];
		delete[] bestChars;
		delete[] bestScore;
	}
	
	bool finished(){
		return pool->isDone();
	}
	
	void draw(){
		for(int i=0;i<(width+w-1)/w;i++)
			for(int j=0;j<(height+h-1)/h;j++)
				drawImage(bestChars[i][j],i*w,j*h);
	}
	
	void nextChar(){
		Image* canvas = pool->next();
		double sum, score;
		for(int x=0, i=0;x<width;x+=w, i++){
			for(int y=0, j=0;y<height;y+=h, j++){
				sum = 0;
				for (int k=0;k<w;k++){
					for (int m=0;m<h;m++){
						if(x+k < width && y+m < height)
							sum += color_dist(canvas->get(k,m),img->get(x+k,y+m));
					}
				}
				score = 1 - (sum / (w*h));
				if(score > bestScore[i][j]){
					bestScore[i][j] = score;
					bestChars[i][j] = canvas;
				}
			}
		}
	}
};