#include "Graphics.h"
#include <iostream>
#define ROUND(a) ((int) (a + 0.5)) //Round function

using namespace std;

int width = -1;//Width of the canvas/screen
int height = -1;//Height of the canvas/screen

HWND myconsole = NULL;//A console handle
HDC mydc = NULL;//A handle to device context (screen)
HDC bufDC = NULL;//The current frame

#ifdef DESKTOP_BG
HDC backupDC = NULL;//The original background
#endif

COLORREF fill_color=RGB(255,255,255);//Color for the fill of shape
COLORREF stroke_color=RGB(0,0,0);//Color for the stroke of shape
bool do_fill = true;//Should shape have fill
bool do_stroke = true;//Should shape have stroke
BYTE alpha_val = 255;//The alpha_val value of the drawn background

int prevH = -1;
Point previous;//Previous point in polygon/vertex
bool first = false;//Did we statred a shape drawing
bool loop = true;//Should the draw function be in loop
long long frameCount = 1;//The number of frames from the bigining of the animation

Image::Image(int width, int height, short Bpp){
    this->width = width;
    this->height = height;
    this->Bpp = Bpp;
    // ((Bpp*width+3) & ~3) is width with padding instead of just Bpp*width
    this->pixels = new char[real_width()*height];
}

int Image::real_width(){
   return ((Bpp*width+3) & ~3);
}

int Image::index(short x, short y){
   return ((Bpp*width+3) & ~3)*(height-1-y)+x*Bpp;
}

COLORREF Image::get(int idx){
	if(idx >= 0 && idx < real_width()*height){
		if (this->Bpp >= 3)
			return RGB(this->pixels[idx+2],this->pixels[idx+1],this->pixels[idx]);
		return RGB(this->pixels[idx],this->pixels[idx],this->pixels[idx]);
	}
	return NULL;
}

COLORREF Image::get(short x,short y){
	if (x < this->width && y < this->height){
		// ((Bpp*width+3) & ~3) is width with padding instead of just Bpp*width
		return get(index(x,y));
	}
	return NULL;
}

void Image::set(int idx, COLORREF color){
	if(idx >= 0 && idx < real_width()*height){
		if (this->Bpp >= 3){
			this->pixels[idx+2] = GetRValue(color);
			this->pixels[idx+1] = GetGValue(color);
		}
		this->pixels[idx] = GetBValue(color);
	}
}

void Image::set(short x,short y, COLORREF color){
	if (x >=0 && y >= 0 && x < this->width && y < this->height){
		// ((Bpp*width+3) & ~3) is width with padding instead of just Bpp*width
		set(index(x,y), color);	
	}
}

Image* Image::crop(int x, int y, int w, int h){
	Image* cropped = new Image(w,h,this->Bpp);
	int x_bytes = x*this->Bpp,
		w_bytes = cropped->real_width(),
		// bitmap is stored in reversed y order
		remaining = this->height - (y+h);
	for(int i=0;i<h;i++){
		memcpy(cropped->pixels+i*w_bytes,
				this->pixels+real_width()*(remaining+i)+x_bytes,
				w_bytes);
	}
	return cropped;
}

Image::~Image(){
    if (this->pixels)
        delete[] this->pixels;
}

Image* loadImage(const char *name){
	Image* img = NULL;
	HDC hCompDC = CreateCompatibleDC(bufDC);
	if (NULL != hCompDC){
		HBITMAP hBMP = (HBITMAP)LoadImageA( NULL, name , IMAGE_BITMAP, 0, 0,
				   LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		if (NULL != hBMP){
			if (NULL != SelectObject(hCompDC, hBMP)){
				BITMAPINFO info = {0};
				info.bmiHeader.biSize = sizeof(info.bmiHeader);
				if(NULL != GetDIBits(hCompDC, hBMP, 0, 0, NULL, &info, DIB_RGB_COLORS)){
					info.bmiHeader.biHeight = abs(info.bmiHeader.biHeight);
					img = new Image(info.bmiHeader.biWidth,
                        info.bmiHeader.biHeight,
                        info.bmiHeader.biBitCount/8);
					GetDIBits(hCompDC, hBMP, 0, info.bmiHeader.biHeight, img->pixels, &info, DIB_RGB_COLORS);
				}
			}
			DeleteObject(hBMP);
		}
        DeleteDC(hCompDC);
	}
	return img;
}

Image* GetCanvas(int x2, int y2, int x, int y){
	Image* img = NULL;
	if (x2 == -1)
		x2 = width;
	if (y2 == -1)
		y2 = height;
	x2 -= x;
	y2 -= y;
	HDC hCompDC = CreateCompatibleDC(bufDC);
	if (NULL != hCompDC){
		HBITMAP hBmp = CreateCompatibleBitmap(bufDC, x2, y2);
		if (NULL != hBmp){
			if (NULL != SelectObject(hCompDC, hBmp)){
				if (NULL != BitBlt(hCompDC, 0, 0, x2, y2, bufDC, x, y, SRCCOPY)){
					img = new Image(x2, y2,3);
					BITMAPINFO info = {0};
					info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
					info.bmiHeader.biWidth = x2;
					info.bmiHeader.biHeight = y2;
					info.bmiHeader.biPlanes = 1;	
					info.bmiHeader.biBitCount = 24;
					info.bmiHeader.biCompression = BI_RGB; 
					GetDIBits(hCompDC, hBmp, 0, y2, img->pixels, &info, DIB_RGB_COLORS);
				}
			}
			DeleteObject(hBmp);
		}
		DeleteDC(hCompDC);
	}
	return img;
}

bool drawImage(Image* img, int x, int y){
    // if(img->hDc){
        // return (NULL != BitBlt(bufDC, x, y, img->width, img->height, *(img->hDc), 0, 0, SRCCOPY));
    // }
    bool success = false;
	HDC hCompDC = CreateCompatibleDC(bufDC);
	if (NULL != hCompDC){
		HBITMAP hBmp = CreateCompatibleBitmap(bufDC, img->width, img->height);
		if (NULL != hBmp){
			BITMAPINFO info = {0};
			info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			info.bmiHeader.biWidth = img->width;
			info.bmiHeader.biHeight = img->height;
			info.bmiHeader.biPlanes = 1;	
			info.bmiHeader.biBitCount = 8*(img->Bpp);
			info.bmiHeader.biCompression = BI_RGB; 
			if (NULL != SetDIBits(hCompDC, hBmp, 0, img->height, img->pixels, &info, DIB_PAL_COLORS)){//DIB_RGB_COLORS)){
				if (NULL != SelectObject(hCompDC, hBmp)){
                    // img->hDc = new HDC();
                    // *(img->hDc) = hCompDC;
					if (NULL != BitBlt(bufDC, x, y, img->width, img->height, hCompDC, 0, 0, SRCCOPY)){
						success = true;
					}
				}
			}
			DeleteObject(hBmp);
		}
		DeleteDC(hCompDC);
	}
	return success;
}

bool SaveBMP(Image* img, const char* bmpfile){
	bool success = false;
	BITMAPFILEHEADER bmfh = {};
	BITMAPINFOHEADER info = {};
	bmfh.bfType = 0x4d42;// 0x4d42 = 'BM'
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = img->width;
	info.biHeight = img->height;
	info.biPlanes = 1;
	info.biBitCount = 8*(img->Bpp);
	info.biCompression = BI_RGB; 
	HANDLE file = CreateFileA(bmpfile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(NULL != file){
		unsigned long bwritten;
		if(TRUE == WriteFile(file, &bmfh, sizeof(BITMAPFILEHEADER), &bwritten, NULL)){	
			if(TRUE == WriteFile(file, &info, sizeof ( BITMAPINFOHEADER ), &bwritten, NULL)){	
				if (TRUE == WriteFile(file, img->pixels, img->real_width()*img->height, &bwritten, NULL )){	
					success = true;
				}
			}
		}
		CloseHandle(file);	
	}
	return success;
}

//get pixel color from canvas/screen
COLORREF GetPixelC(int x,int y){
	return GetPixel(bufDC,x,y);
}

//set pixel color at given point on the canvas/screen
void SetPixelC(float x, float y){
	COLORREF color = do_fill ? fill_color : stroke_color;
	if (alpha_val != 255){
		COLORREF C = GetPixelC(x,y);
		double a = alpha_val/255.0;
		BYTE r = GetRValue(color)*a+GetRValue(C)*(1-a);
		BYTE g = GetGValue(color)*a+GetGValue(C)*(1-a);
		BYTE b = GetBValue(color)*a+GetBValue(C)*(1-a);
		color = RGB(r,g,b);
	}
	SetPixelV(bufDC, ROUND(x), ROUND(y),color);
}

//Set the fill color of shapes
void fill(COLORREF color){
	fill_color = color;
	do_fill = true;
}

//Set the stroke color of shapes
void stroke(COLORREF color){
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
	int dx = x1 - x0, dy = y1 - y0, steps;
	float xIncrement, yIncrement, x = x0, y = y0;
	
	steps = max(abs(dx), abs(dy));
	xIncrement = dx / (float) steps;
	yIncrement = dy / (float) steps;
	SetPixelC(x,y);

	for(int k = 0; k < steps; k++){
		x += xIncrement;
		y += yIncrement;
		SetPixelC(x,y);
	}
}

//Draw rectangle with left-top corner in (x0,y0) and width=w and height=h
void drawRectangle(int x, int y, int w, int h){
	if (do_fill){
		for(int i = x; i <= x+w; i ++){
			for(int j = y; j <= y+h; j ++){
				SetPixelC(i,j);
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
		if (prevH != yc+y){
			drawLine(xc+x, yc+y, xc-x, yc+y);
			if (y != 0){
				drawLine(xc+x, yc-y, xc-x, yc-y);
			}
		}
		prevH = yc+y;
	}
	else{
		SetPixelC(xc+x, yc+y);
		if(y != 0)
			SetPixelC(xc+x, yc-y);
		if(x != 0){
			SetPixelC(xc-x, yc+y);
			if (y != 0)
				SetPixelC(xc-x, yc-y);
		}
	}
}

//Draw ellipse in (x,y) with constants a=rx and b=ry
void _drawEllipse(int x0, int y0, int rx, int ry){
    prevH = -1;
	
	int rxSq = rx * rx;
    int rySq = ry * ry;
    int x = 0, y = ry;
	float p;
    int px = 0, py = 2 * rxSq * y;

    doEllipse(x0, y0, x, y);

    //Region 1
    p = (float)(rySq - (rxSq * ry) + (0.25 * rxSq));
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
    p = (float)(rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq);
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

Point getTextSize(const char* txt, int len){
	SIZE size;
	GetTextExtentPoint32A(bufDC, txt, len, &size);
	return Point(size.cx,size.cy);
}

Point getTextSize(const wchar_t* txt, int len){
	SIZE size;
	GetTextExtentPoint32W(bufDC, txt, len, &size);
	return Point(size.cx,size.cy);
}

//Draw unicode text of length = len, in (x,y) 
Point drawText(int x0, int y0,const wchar_t* txt, int len){
	if (do_fill)
		SetTextColor(bufDC,fill_color);
	else
		SetTextColor(bufDC,stroke_color);
	SetBkMode(bufDC,TRANSPARENT);
	Point size = getTextSize(txt,len);
	RECT rect = { x0, y0, x0+(int)size.x, y0+(int)size.y };
	ExtTextOutW(bufDC, x0, y0, NULL, &rect, txt, len, NULL);
	SetBkMode(bufDC,OPAQUE);
	return size;
}

//Draw ascii text of length = len, in (x,y) 
Point drawText(int x0, int y0,const char* txt, int len){
	COLORREF color = do_fill ? fill_color : stroke_color;
	SetTextColor(bufDC,fill_color);
	SetBkMode(bufDC,TRANSPARENT);
	Point size = getTextSize(txt,len);
	RECT rect = { x0, y0, x0+(int)size.x, y0+(int)size.y };
	ExtTextOutA(bufDC, x0, y0, NULL, &rect, txt, len, NULL);
	SetBkMode(bufDC,OPAQUE);
	return size;
}

//Set the text size in pixels for text drawings 
void textSize(int size){
	// HFONT hFont = (HFONT)GetCurrentObject(bufDC,OBJ_FONT);
	// HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	HFONT hFont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
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

#ifdef DESKTOP_BG
//Funtion to find child of the hwnd (find the desktop handle)
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam){
	HWND p = FindWindowEx(hwnd, NULL,"SHELLDLL_DefView", NULL);
    if (p != NULL)
    {
        // Gets the WorkerW Window after the current one.
        myconsole = FindWindowEx(NULL, hwnd, "WorkerW", NULL);
        DeleteObject(p);
        return FALSE;
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
	DeleteObject(parentFolderView);
	EnumWindows(EnumWindowsProc, NULL);
}
#endif

//Set the background of each frame
void background(COLORREF bg){
	HDC tmpDC = NULL;
	Clone(bufDC, tmpDC);
	#ifdef DESKTOP_BG
	BitBlt(tmpDC, 0, 0, width, height, backupDC, 0, 0, SRCCOPY);
	#endif
	#ifndef DESKTOP_BG
	HBRUSH hBrush = CreateSolidBrush(bg);
	RECT rect = {0,0,width,height};
	FillRect(tmpDC,&rect,hBrush);
	DeleteObject(hBrush);
	#endif
	if (alpha_val == 255){
		BitBlt(bufDC,0,0,width,height,tmpDC,0, 0,SRCCOPY);
	}else{
		BLENDFUNCTION blend = {AC_SRC_OVER, 0, alpha_val, 0};
		AlphaBlend(bufDC, 0, 0, width, height, tmpDC, 0, 0 , width, height, blend);
	}
	DeleteDC(tmpDC);
}

void alpha(BYTE alpha){
	alpha_val = alpha;
}

//Generate rainbow color based on j
COLORREF rainbowColors(int j){
	float frequency = 0.3f;
	int red,green,blue;
	red   = (int)(sin(frequency*j + 0) * 127 + 128);
	green = (int)(sin(frequency*j + 2) * 127 + 128);
	blue  = (int)(sin(frequency*j + 4) * 127 + 128);
	return RGB(red,green,blue);
}

//Colen the HDC in dst into the HDC in src
void Clone(HDC& src, HDC& dst){
	dst = CreateCompatibleDC(src);
	HBITMAP hbmMem = CreateCompatibleBitmap(src, width, height);
	SelectObject(dst, hbmMem);
	DeleteObject(hbmMem);
}

void hideCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursoInfo;
	CursoInfo.dwSize = 1;         /* The size of caret */
	CursoInfo.bVisible = false;   /* Caret is visible? */
	SetConsoleCursorInfo(hConsole, &CursoInfo);
}

void hideScrollBar(){
	ShowScrollBar(myconsole, SB_BOTH, FALSE);
}

//Create all the handles for the animation
void InitCanvas(bool fullscreen){
	#ifdef DESKTOP_BG
	findDesktopBackGround(); 
	#else
	myconsole = GetConsoleWindow();
	#endif
    if (myconsole != NULL)
	{
		hideCursor();
		hideScrollBar();
		mydc = GetDC(myconsole);
		if (mydc != NULL)
		{
			if(fullscreen){
				width = GetDeviceCaps(mydc,HORZRES);
				height = GetDeviceCaps(mydc,VERTRES);
			}
			Clone(mydc, bufDC);
			BitBlt(bufDC, 0, 0, width, height, mydc, 0, 0, SRCCOPY);
			#ifdef DESKTOP_BG
			Clone(mydc, backupDC);
			BitBlt(backupDC, 0, 0, width, height, mydc, 0, 0, SRCCOPY);
			#endif
		} else{
			cout << "Error: device context not found" << endl;
		}
		
	}
	else{
		cout << "Error: console window not found" << endl;
	}
}

void createCanvas(){
	InitCanvas(true);
}

void createCanvas(int w, int h){
	width = w;
	height = h;
	InitCanvas(false);
}

//Draw the current frame of animation
void doDraw(){
	BitBlt(mydc,0,0,width,height,bufDC,0, 0,SRCCOPY);
}

void nextFrame(){
	frameCount++;
}

bool getLoop(){
	return loop;
}

//Stop the draw loop
void noLoop(){
	loop = false;
}

void Finish(){
	ReleaseDC(myconsole, mydc);
	ReleaseDC(myconsole, bufDC);
	#ifdef DESKTOP_BG
	ReleaseDC(myconsole, backupDC);
	#endif
	cin.ignore();
}

bool isFocused(){
	return (GetForegroundWindow() == myconsole);
}

//Run the drawing in loop until noLoop() is called
int main() {
	setup();
	do{
		draw();
		doDraw();
		nextFrame();
	}while(getLoop());
	Finish();
	return 0;
}