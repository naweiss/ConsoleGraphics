#include <windows.h>
#include <iostream>

using namespace std;

int main() 
{
	//Get a console handle
    HWND myconsole = GetConsoleWindow();
    if (myconsole == NULL)
	{
		cout << "Error: console window not found" << endl;
		return 0;
	}
	//Get a handle to device context
    HDC hDC = GetDC(myconsole);
    if (hDC == NULL)
	{
		cout << "Error: device context not found" << endl;
		return 0;
	}
	HDC hDCMem = CreateCompatibleDC(hDC);
  
    int rect_w = 1000, rect_h = 500;
	unsigned char* lpBitmapBits;

	BITMAPINFO bi; 
	ZeroMemory(&bi, sizeof(BITMAPINFO));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = rect_w;
	bi.bmiHeader.biHeight = -rect_h;  //negative so (0,0) is at top left
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32; // or 16 or 24
	
	
	HBITMAP bitmap = ::CreateDIBSection(hDCMem, &bi, DIB_RGB_COLORS,  (VOID**)&lpBitmapBits, NULL, 0);
	HGDIOBJ oldbmp = ::SelectObject(hDCMem, bitmap); 

	BitBlt(hDCMem, 0, 0, rect_w, rect_h, hDC, 0, 0, SRCCOPY);

	int pitch = 4*rect_w; // 4 bytes per pixel but if not 32 bit, round pitch up to multiple of 4
	int index;
	for(int x=0; x<500; x=x++)
	{
		for(int y=0; y<200; y++)
		{
			index = y * pitch;  
            index += x*4;
			if ((x+y)%2 == 0){
			lpBitmapBits[index + 0] = 87;  // blue
			lpBitmapBits[index + 1] = 122; // green
			lpBitmapBits[index + 2] = 185;  // red 
			}
		}
	}

	 
	BitBlt(hDC, 0, 0, rect_w, rect_h, hDCMem, 0, 0, SRCCOPY);


	SelectObject(hDCMem,oldbmp);  
	DeleteDC(hDCMem);  
	DeleteObject(bitmap);
	cin.ignore();
}