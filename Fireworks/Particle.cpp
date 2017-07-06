#include "Vector.cpp"
#include "Graphics.cpp"

class Particle{
private:
	bool firework;
	COLORREF color;
public:
	Vector* pos;
	Vector* vel;
	Vector* acc;
	Particle(float x, float y, COLORREF color, bool firework = true){
		this->firework = firework;
		this->color = color;
		pos = new Vector(x,y);
		if (firework){
			float ran = RandomF(8,13);
			vel = new Vector(0,-ran);
		} else {
			vel = new Vector(Vector::random2D());
			*vel *= RandomF(2,10);
		}
		acc = new Vector(0,0);
	}
	
	~Particle(){
		delete pos;
		delete vel;
		delete acc;
	}
	
	void applyForce(const Vector& force){
		*acc += force;
	}
	
	void update(){
		if (!firework){
			*vel *= 0.9;
		}
		*vel += *acc;
		*pos += *vel;
		*acc *= 0;
	}
	
	void show(){
		fill(color);
		drawCircle(pos->x,pos->y,3);
	}
};