#include <windows.h>
#include <iostream>
//#define DESKTOP_BG_ //Console window as desktop background
//#define OVERLAY_BG_ //Console window shold merge with existing bacground
#define ROUND(a) ((int) (a + 0.5)) //Round function

using namespace std;

//Struct for point in 2d
struct Point{
   int x;
   int y;
   COLORREF color;
};

static HWND myconsole = NULL;//A console handle
static HDC mydc = NULL;//A handle to device context (screen)
static HDC bufDC = NULL;//The current frame
static int width = -1;//Width of the canvas/screen
static int height = -1;//Height of the canvas/screen
#ifdef DESKTOP_BG_
static HDC backupDC = NULL;//The original background
#endif

static COLORREF fill_color=RGB(255,255,255);//Color for the fill of shape
static COLORREF stroke_color=RGB(255,255,255);//Color for the stroke of shape
static bool do_fill = true;//Should shape have fill
static bool do_stroke = true;//Should shape have stroke
static BYTE bg_alpha = 0;//The alpha value of the drawn background

static Point previous;//Previous point in polygon/vertex
static bool first = false;//Did we statred a shape drawing
static bool loop = true;//Should the draw function be in loop
static long long frameCount = 0;//The number of frames from the bigining of the animation

//Set the fill color of shapes
void fill(COLORREF color=RGB(255,255,255)){
	fill_color = color;
	do_fill = true;
}

//Set the stroke color of shapes
void stroke(COLORREF color=RGB(255,255,255)){
	stroke_color = color;
	do_stroke = true;
}

//Disable shapes fill
void noFill(){
	do_fill = false;
}

//Disable shapes strokes
void noStroke(){
	do_stroke = false;
}

//Draw line form (x0,y0) to (x1,y1)
void drawLine(int x0, int y0, int x1, int y1){

   int dx = x1 - x0, dy = y1 - y0, steps, k;

   float xIncrement, yIncrement, x = x0, y = y0;

   if(abs(dx) > abs(dy)) steps = abs(dx);

   else steps = abs(dy);

   xIncrement = dx / (float) steps;

   yIncrement = dy / (float) steps;

   if (do_fill){
	   SetPixelV(bufDC, ROUND(x), ROUND(y),fill_color);
   }
   else{
		SetPixelV(bufDC, ROUND(x), ROUND(y),stroke_color);
   }

   for(int k = 0; k < steps; k++){

    x += xIncrement;

    y += yIncrement;

	if (do_fill){
		SetPixelV(bufDC, x, y, fill_color);
	}
	else{
		SetPixelV(bufDC, x, y, stroke_color);
	}

 }

}

//Draw rectangle with left-top corner in (x0,y0) and width=w and height=h
void drawRectangle(int x, int y, int w, int h){
	if (do_fill){
		for(int i = x; i <= x+w; i ++){
			for(int j = y; j <= y+h; j ++){
				SetPixelV(bufDC, i, j, fill_color);
			}
		}
	}
	if (do_stroke){
		bool tmp = do_fill;
		do_fill = false;
		drawLine(x,y,x+w,y);
		drawLine(x,y,x,y+h);
		drawLine(x,y+h,x+w,y+h);
		drawLine(x+w,y,x+w,y+h);
		do_fill = tmp;
	}
}

//Draw pixels section in ellipse
void doEllipse(int xc, int yc, int x, int y){
	if (do_fill){
		drawLine(xc+x, yc+y, xc-x, yc+y);
		drawLine(xc+x, yc-y, xc-x, yc-y);
	}
	else{
		/*This function plots a pixel at coordinates(x,y) specified by first 2 arguments and third argument specifies the color of the pixel*/
		SetPixelV(bufDC, xc+x, yc+y, stroke_color);
		SetPixelV(bufDC, xc-x, yc+y, stroke_color);
		
		SetPixelV(bufDC, xc+x, yc-y, stroke_color);
		SetPixelV(bufDC, xc-x, yc-y, stroke_color);
	}
}

//Draw ellipse in (x,y) with constants a=rx and b=ry
void _drawEllipse(int x0, int y0, int rx, int ry){
    int rxSq = rx * rx;
    int rySq = ry * ry;
    int x = 0, y = ry;
	float p;
    int px = 0, py = 2 * rxSq * y;

    doEllipse(x0, y0, x, y);

    //Region 1
    p = rySq - (rxSq * ry) + (0.25 * rxSq);
    while (px < py)
    {
        x++;
        px = px + 2 * rySq;
        if (p < 0)
            p = p + rySq + px;
        else
        {
            y--;
            py = py - 2 * rxSq;
            p = p + rySq + px - py;
        }
        doEllipse(x0, y0, x, y);
    }

    //Region 2
    p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
    while (y > 0)
    {
        y--;
        py = py - 2 * rxSq;
        if (p > 0)
            p = p + rxSq - py;
        else
        {
            x++;
            px = px + 2 * rySq;
            p = p + rxSq - py + px;
        }
        doEllipse(x0, y0, x, y);
    }
}

//Draw Ellipse with center in (x0,y0) and a=rx and b=ry
void drawEllipse(int x0, int y0, int rx, int ry){
	if (do_fill){
		_drawEllipse(x0,y0,rx,ry);
	}
	if(do_stroke){
		bool tmp = do_fill;
		do_fill = false;
		_drawEllipse(x0,y0,rx,ry);
		do_fill = tmp;
	}
}

//Draw Ellipse with center in (x0,y0) and radius=r
void drawCircle(int x0, int y0, int r){
	drawEllipse(x0,y0,r,r);
}

//Draw unicode text of length = len, in (x,y) 
void drawText(int x0, int y0,wchar_t* txt, int len){
	SetTextColor(bufDC,fill_color);
	SetBkMode(bufDC,TRANSPARENT);
	TextOutW(bufDC, x0, y0, TEXT(txt),len);
	SetBkMode(bufDC,OPAQUE);
}

//Draw ascii text of length = len, in (x,y) 
void drawText(int x0, int y0,const char* txt, int len){
	SetTextColor(bufDC,fill_color);
	SetBkMode(bufDC,TRANSPARENT);
	TextOut(bufDC, x0, y0, TEXT(txt),len);
	SetBkMode(bufDC,OPAQUE);
}

//Set the text size in pixels for text drawings 
void textSize(int size){
	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	LOGFONT logfont;
	GetObject(hFont, sizeof(LOGFONT), &logfont);
	
	// Now change the logfont.lfHeight member
	logfont.lfHeight = -size; // in pixles
		
	HFONT hNewFont = CreateFontIndirect(&logfont);
	SelectObject(bufDC, hNewFont);
}

//Start shape drawing
void beginShape(){
	first = true;
}

//beginShape() must be called befor the first vertex
//Add point to the shape/polygon
void vertex(Point p){
	if (!first){
		drawLine(previous.x,previous.y,p.x,p.y);
	}
	first = false;
	previous = p;
}

//Set the background of each frame
void background(COLORREF bg = RGB(0,0,0), BYTE alpha = 0){
	bg_alpha = alpha;
	HBRUSH hBrush = CreateSolidBrush(bg);
	RECT rect;
	GetClientRect(myconsole, &rect);
	FillRect(bufDC,&rect,hBrush);
	DeleteObject(hBrush);
}

#ifdef DESKTOP_BG_
//Funtion to find child of the hwnd (find the desktop handle)
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam){
	HWND p = FindWindowEx(hwnd, NULL,"SHELLDLL_DefView", NULL);
    if (p != NULL)
    {
        // Gets the WorkerW Window after the current one.
        myconsole = FindWindowEx(NULL, hwnd, "WorkerW", NULL);
    }
	return TRUE;
}


//Function to locate the handle of the desktop
void findDesktopBackGround(){
	HWND parentFolderView = ::FindWindowExW(0, 0, L"Progman", L"Program Manager");
	if (parentFolderView == NULL){
		cout << "Error: ProgMan window not found" << endl;
		return;
	}
	LRESULT success = SendMessageTimeout(
		parentFolderView,
		0x052C,
		0,
		NULL,
		SMTO_NORMAL,
		1000,
		NULL
	);
	EnumWindows(EnumWindowsProc, NULL);
}
#endif

//Colen the HDC in dst into the HDC in src
void Clone(HDC& src, HDC& dst){
	dst = CreateCompatibleDC(src);
	HBITMAP hbmMem = CreateCompatibleBitmap(src, width, height);
	SelectObject(dst, hbmMem);
}

//Create all the handles for the animation
void InitCanvas(){
	#ifdef DESKTOP_BG_
	findDesktopBackGround(); 
	#else
	myconsole = GetConsoleWindow();
	#endif
    if (myconsole != NULL)
	{
		mydc = GetDC(myconsole);
		if (mydc != NULL)
		{
			width = GetDeviceCaps(mydc,HORZRES);
			height = GetDeviceCaps(mydc,VERTRES);
			#ifdef DESKTOP_BG_
			Clone(mydc, backupDC);
			BitBlt(backupDC, 0, 0, width, height, mydc, 0, 0, SRCCOPY);
			#endif
			Clone(mydc, bufDC);
			background();
		}
		else{
			cout << "Error: device context not found" << endl;
		}
		
	}
	else{
		cout << "Error: console window not found" << endl;
	}
}

//Generate rainbow color based on j
COLORREF rainbowColors(int j){
	float frequency = 0.3;
	int red,green,blue;
	red   = sin(frequency*j + 0) * 127 + 128;
	green = sin(frequency*j + 2) * 127 + 128;
	blue  = sin(frequency*j + 4) * 127 + 128;
	return RGB(red,green,blue);
}

//Return random number between 0 and max not including max
int Random(int max){
	return rand() % max;
}

//Return random number between min and max not including max
int Random(int min, int max){
	return Random(max-min) + min;
}

//Stop the draw loop
void noLoop(){
	loop = false;
}

//Draw the current frame of animation
void doDraw(){
	if (bg_alpha == 0){
		BitBlt(mydc,0,0,width,height,bufDC,0, 0,SRCCOPY);
	}else{
		BLENDFUNCTION blend = {AC_SRC_OVER, 0, bg_alpha, 0};
		AlphaBlend(mydc, 0, 0, width, height, bufDC, 0, 0 , width, height, blend);
	}
	#ifdef DESKTOP_BG_
	#ifdef OVERLAY_BG_
	BLENDFUNCTION blend = {AC_SRC_OVER, 0, 100, 0};
	AlphaBlend(mydc,0,0,width,height,backupDC,0, 0,width,height, blend);
	#endif
	#endif
}

//Prototype for the initialization of the program
void setup();

//Prototype for each frame draw
void draw();

//Run the drawing in loop until noLoop() is called
int main() {
	InitCanvas();
	setup();
	do{
		draw();
		doDraw();
		frameCount++;
		Sleep(16);
	}while(loop);
	ReleaseDC(myconsole, mydc);
	cin.ignore();
	return 0;
}