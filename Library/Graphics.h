#include <Windows.h>

/** The axes are defined the following way:
	x-axis: from left to right
	y-axis: from top to bottom
**/

// #define DESKTOP_BG //Console window as desktop background

extern int width;//Width of the canvas/screen
extern int height;//Height of the canvas/screen
extern long long frameCount;//The number of frames from the bigining of the animation

//Struct for point in 2d
struct Point{
   float x;
   float y;
   float z;
   COLORREF color;
   Point(){}
   Point(float x, float y, float z = 0){
	   this->x = x;
	   this->y = y;
	   this->z = z;
   }
};

struct Image{
	int width;
	int height;
	short Bpp;
	char* pixels;
    // HDC* hDc = NULL;
	
	Image(int width, int height, short Bpp);
	int real_width();
	int index(short i, short j);
	
    COLORREF get(int idx);
	COLORREF get(short x,short y);
    void set(int idx, COLORREF color);
	void set(short x,short y, COLORREF color);
	
	Image* crop(int x, int y, int w, int h);
	
	~Image();
};

//get pixel color from canvas/screen
COLORREF GetPixelC(int x,int y);

void SetPixelC(float x,float y);

//Set the fill color of shapes
void fill(COLORREF color=RGB(255,255,255));

//Set the stroke color of shapes
void stroke(COLORREF color=RGB(0,0,0));

//Disable shapes fill
void noFill();

//Disable shapes strokes
void noStroke();

//Draw line form (x0,y0) to (x1,y1)
void drawLine(int x0, int y0, int x1, int y1);

void lineThickness(int t);

//Draw rectangle with left-top corner in (x0,y0) and width=w and height=h
void drawRectangle(int x, int y, int w, int h);

//Draw pixels section in ellipse
void doEllipse(int xc, int yc, int x, int y);

//Draw ellipse in (x,y) with constants a=rx and b=ry
void _drawEllipse(int x0, int y0, int rx, int ry);

//Draw Ellipse with center in (x0,y0) and a=rx and b=ry
void drawEllipse(int x0, int y0, int rx, int ry);

//Draw Ellipse with center in (x0,y0) and radius=r
void drawCircle(int x0, int y0, int r);

Point getTextSize(const char* txt, int len);
Point getTextSize(const wchar_t* txt, int len);

//Draw unicode text of length = len, in (x,y) 
Point drawText(int x0, int y0,const wchar_t* txt, int len);

//Draw ascii text of length = len, in (x,y) 
Point drawText(int x0, int y0,const char* txt, int len);

//Set the text size in pixels for text drawings 
void textSize(int size);

//Start shape drawing
void beginShape();

//beginShape() must be called befor the first vertex
//Add point to the shape/polygon
void vertex(Point p);

void alpha(BYTE alpha_val = 255);

//Set the background of each frame
void background(COLORREF bg = RGB(0,0,0));

//Generate rainbow color based on j
COLORREF rainbowColors(int j);

//Stop the draw loop
void noLoop();

Image* loadImage(const char *name);

Image* GetCanvas(int x2 = -1, int y2 = -1, int x = 0, int y =0);

bool drawImage(Image* img, int x = 0, int y = 0);

bool SaveBMP(Image* img, LPCTSTR bmpfile);

void createCanvas();

void createCanvas(int w, int h);

bool isFocused();

void pause();

//Prototype for the initialization of the program
void setup();

//Prototype for each frame draw
void draw();
