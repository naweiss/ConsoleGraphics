#include "Math.h"

//Return random double number between fMin and fMax not including fMax
float RandomF(float fMin, float fMax)
{
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

//Return random double number between 0 and fMax not including fMax
float RandomF(float fMax)
{
    double f = (double)rand() / RAND_MAX;
    return f * fMax;
}

//Return random number between 0 and max not including max
unsigned int Random(unsigned int max){
	return rand() % max;
}

//Return random number between min and max not including max
unsigned int Random(unsigned int min, unsigned int max){
	return Random(max-min) + min;
}