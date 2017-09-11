#include "Particle.h"
#include <vector>

class Firework{
	static Vector* gravity;
	Particle* firework;
	vector<Particle*> particles;
	int lifespan;
	COLORREF color;
public:
	Firework(COLORREF color);
	
	~Firework();
	
	bool dead();
	
	void expload();
	
	void update();
	
	bool done();
	
	void show();
};