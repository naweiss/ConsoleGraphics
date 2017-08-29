#include <stdlib.h>  
#define PI	3.14159265358979323846
#define HALF_PI	PI/2
#define TWO_PI	PI*2

//Return random double number between fMin and fMax not including fMax
float RandomF(float fMin, float fMax);

//Return random double number between 0 and fMax not including fMax
float RandomF(float fMax);

//Return random number between 0 and max not including max
unsigned int Random(unsigned int max);

//Return random number between min and max not including max
unsigned int Random(unsigned int min, unsigned int max);