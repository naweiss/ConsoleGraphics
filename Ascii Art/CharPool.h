#define POOL_SIZE 95
// #define POOL_SIZE 5

char Latter(int code){
	return (char)code;
}

class CharPool{
	char pool[POOL_SIZE];
	int pool_index;
public:
	CharPool(){
		restart();
		#if POOL_SIZE == 95
			int count = 0;
			for (int i = 32; i < 127; i++){
				pool[count++] = Latter(i);
			}
		#else
			pool[0] = Latter(32);
			pool[1] = Latter(45);
			pool[2] = Latter(95);
			pool[3] = Latter(124);
			pool[4] = Latter(46);
		#endif
	}
	
	void restart(){
		pool_index = 0;
	}
	
	bool isDone(){
		return pool_index == POOL_SIZE;
	}
	
	char next(){
		return pool[pool_index++];
	}
};