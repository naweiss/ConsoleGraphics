#include "Graphics.cpp"
#include "Vector.cpp"
#include <string>
#include <ctime>

short n = 10, pop = 5, num = 0;
int l,r,t,b;
Vector** triangles;

float sign(Vector p1, Vector p2, Vector p3){
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool inside_triangle(Vector pt, short index){
    bool b1, b2, b3;

    b1 = sign(pt, triangles[index][0], triangles[index][1]) < 0.0f;
    b2 = sign(pt, triangles[index][1], triangles[index][2]) < 0.0f;
    b3 = sign(pt, triangles[index][2], triangles[index][0]) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

void random_triangle(short index){
	triangles[index] = new Vector[3];
	for (short i = 0;i < 3;i++){
		Vector tmp = Vector::random2D();
		tmp.x *= RandomF(width/2);
		tmp.y *= RandomF(height/2);
		triangles[index][i] = tmp+Vector(width/2,height/2);
		if (triangles[index][i].x < r)
			r = triangles[index][i].x;
		if (triangles[index][i].y < b)
			b = triangles[index][i].y;
		if (triangles[index][i].x > l)
			l = triangles[index][i].x;
		if (triangles[index][i].y > t)
			t = triangles[index][i].y;
	}
}

void fill_triangle(short index){
	for (int i = r;i < l;i++){
		for (int j = b;j < t;j++){
			if (inside_triangle(Vector(i,j), index)){
				SetPixelC(i,j);
			}
		}
	}
}

void setup(){
	srand(time(NULL));
	textSize(200);
	width = height = 400;
	r = width;
	b = height;
	l = t = 0;
	triangles = new Vector*[n];
}

void draw(){
	background();
	for (int i=0;i<n;++i){
		random_triangle(i);
		fill(RGB(Random(256),Random(256),Random(256)));
		fill_triangle(i);
	}
	num++;
	if (pop == num){
		for(short i = 0; i < n; ++i) {
			delete[] triangles[i];
		}
		delete[] triangles;
		fill();
		string passed = to_string(pop);
		drawText(width/2-100,height/2-100,passed.c_str(),passed.length());
		noLoop();
	}
}