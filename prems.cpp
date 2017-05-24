#include "Graphics.cpp"

static const int VALS_SIZE = 3;
static int vals[VALS_SIZE];

void setup(){
	for (int i = 0; i < VALS_SIZE; i++){
		vals[i] = i;
	}
}


void swap(int& p1,int& p2){
	int tmp = p1;
	p1 = p2;
	p2 = tmp;
}

void Reverse(int start,int end)
{
	for (int i = start; i <= start+(end-start)/2; i++){
		swap(vals[i],vals[end-(i-start)]);
	}
}

void draw(){
	//background();
	
	string str = "";
	for (int i = 0; i < VALS_SIZE; i++)
		str += vals[i] + " ";
	drawText(0,0,str.c_str(),str.length());
	
	int largestI = -1;
	for (int i = 0; i < VALS_SIZE-1; i++){
		if (vals[i] <vals[i+1])
			largestI = i;
	}
	if(largestI == -1){
		noLoop();
		str = "finished";
		drawText(0,0,str.c_str(),str.length());
		return;
	}
	int largestJ = -1;
	for (int j = 0; j < VALS_SIZE; j++){
		if (vals[largestI] < vals[j])
			largestJ = j;
	}
	
	swap(vals[largestI],vals[largestJ]);
	
	Reverse(largestI+1,VALS_SIZE-1);
	
}