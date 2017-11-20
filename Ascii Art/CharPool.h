#include "Maths.h"
#define POOL_SIZE 2

class CharPool{
	char pool[POOL_SIZE];
public:
	CharPool(){
		// int count = 0;
		// for (int i = 32; i < 127; i++){
			// pool[count++] = (char)(i);
		// }
		// for (int i = 176; i < 255; i++){
			// pool[count++] = (char)(i);
		// }
		pool[0] = (char)(32);
		pool[1] = (char)(46);
	}
	
	char rand(){
          return pool[Random(POOL_SIZE)];
	}
};