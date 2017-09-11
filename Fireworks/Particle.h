#include "Vector.h"
#include "Graphics.h"

class Particle{
private:
	bool firework;
	COLORREF color;
public:
	Vector* pos;
	Vector* vel;
	Vector* acc;
	Particle(float x, float y, COLORREF color, bool firework = true);
	
	~Particle();
	
	void applyForce(const Vector& force);
	
	void update();
	
	void show();
};