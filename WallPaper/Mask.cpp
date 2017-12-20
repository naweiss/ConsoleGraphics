#include "Graphics.h"
#include <iostream>

using namespace std;

class Mask{
private:
    COLORREF mask;
    double threshold;
    Image* bg;
public:
    Mask(COLORREF mask, Image* bg, double threshold = 0.45){
        this->mask = mask;
        this->bg = bg;
        this->threshold = threshold;
    }
    
    COLORREF color_mask(COLORREF c, int idx){
        double dist = color_dist(c,mask);
        return blend(c,
            bg->get(idx),
            20*(dist-threshold));
    }
    
    static double color_dist(COLORREF color1,COLORREF color2){
        double r = pow((GetRValue(color1)-GetRValue(color2))/255.0,2);
        double g = pow((GetGValue(color1)-GetGValue(color2))/255.0,2);
        double b = pow((GetBValue(color1)-GetBValue(color2))/255.0,2);
        return sqrt((2*r + 4*g + 3*b)/8);
    }
    
    static COLORREF blend(COLORREF source,COLORREF dest,double a){
        if(a >= 1)
            return source;
        if(a <= 0)
            return dest;
        int r = (a * GetRValue(source))+(GetRValue(dest)*(1-a));
        int g = (a * GetGValue(source))+(GetGValue(dest)*(1-a));
        int b = (a * GetBValue(source))+(GetBValue(dest)*(1-a));
        return RGB(r,g,b);
    }
};