#include <Windows.h>

// #define DESKTOP_BG //Console window as desktop background

extern int width;//Width of the canvas/screen
extern int height;//Height of the canvas/screen
extern long long frameCount ;//The number of frames from the bigining of the animation

//Struct for point in 2d
struct Point{
   float x;
   float y;
   COLORREF color;
   Point(){}
   Point(float x,float y){
	   this->x = x;
	   this->y = y;
   }
};

struct Image{
	int width;
	int height;
	int Bpp;
	BYTE* pixels;
	
	Image(int width, int height, int Bpp) {
		this->width = width;
		this->height = height;
		this->Bpp = Bpp;
		// ((Bpp*width+3) & ~3) is width with padding instead of just Bpp*width
		this->pixels = new BYTE[((Bpp*width+3) & ~3)*height];
	}
	
	COLORREF get(int x,int y){
		if (x < this->width && y < this->height){
			// ((Bpp*width+3) & ~3) is width with padding instead of just Bpp*width
			int index = (this->height-1-y)*((this->width*this->Bpp+3)& ~3)+x*this->Bpp;
			
			return RGB(this->pixels[index+2],this->pixels[index+1],this->pixels[index]);
		}
		return NULL;
	}
	
	void set(int x,int y, COLORREF color){
		if (x >=0 && y >= 0 && x < this->width && y < this->height){
			// ((Bpp*width+3) & ~3) is width with padding instead of just Bpp*width
			int index = (this->height-1-y)*((this->width*this->Bpp+3)& ~3)+x*this->Bpp;
			
			this->pixels[index+2] = GetRValue(color);
			this->pixels[index+1] = GetGValue(color);
			this->pixels[index]   = GetBValue(color);
		}
	}
	
	~Image() {
		if (this->pixels)
			delete[] this->pixels;
    }
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

//Draw unicode text of length = len, in (x,y) 
void drawText(int x0, int y0,wchar_t* txt, int len);

//Draw ascii text of length = len, in (x,y) 
void drawText(int x0, int y0,const char* txt, int len);

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

//Colen the HDC in dst into the HDC in src
void Clone(HDC& src, HDC& dst);

//Create all the handles for the animation
void InitCanvas();

//Generate rainbow color based on j
COLORREF rainbowColors(int j);

//Stop the draw loop
void noLoop();

//Draw the current frame of animation
void doDraw();

Image* loadImage(const char *name);

Image* GetCanvas(int x2 = -1, int y2 = -1, int x = 0, int y =0);

bool drawImage(Image* img, int x = 0, int y = 0);

bool SaveBMP(Image* img, LPCTSTR bmpfile);

void nextFrame();

bool getLoop();

void Finish();

bool isFocused();

//Prototype for the initialization of the program
void setup();

//Prototype for each frame draw
void draw();