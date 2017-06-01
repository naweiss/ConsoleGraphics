#include <ostream>
#include "Math.cpp"
using namespace std;

class Vector{
private:
	double x;
	double y;
	double z;
public:
	Vector(double x = 0,double y = 0 , double z = 0){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	Vector(const Vector &obj) {
		this->x = obj.x;
		this->y = obj.y;
		this->z = obj.z;
	}
	
	void set(double x = 0,double y = 0 , double z = 0){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	bool operator==(const Vector& obj){
		return ((x == obj.x) && (y == obj.y) && (z == obj.z));
	}
	
	Vector& operator+(const Vector& obj){
		Vector result;
		result.x = this->x + obj.x;
		result.y = this->y + obj.y;
		result.z = this->z + obj.z;
		return result;
	}
	
	Vector& operator+=(const Vector& obj){
		this->x += obj.x;
		this->y += obj.y;
		this->z += obj.z;
		return *this;
	}
	
	Vector& operator-(const Vector& obj){
		Vector result;
		result.x = this->x - obj.x;
		result.y = this->y - obj.y;
		result.z = this->z - obj.z;
		return result;
	}
	
	
	Vector& operator-=(const Vector& obj){
		this->x -= obj.x;
		this->y -= obj.y;
		this->z -= obj.z;
		return *this;
	}
	
	Vector& operator*(const double n){
		Vector result;
		result.x = this->x * n;
		result.y = this->y * n;
		result.z = this->z * n;
		return result;
	}
	
	
	Vector& operator*=(const double n){
		this->x *= n;
		this->y *= n;
		this->z *= n;
		return *this;
	}
	
	Vector& operator/(const double n){
		Vector result;
		result.x = this->x / n;
		result.y = this->y / n;
		result.z = this->z / n;
		return result;
	}
	
	
	Vector& operator/=(const double n){
		this->x /= n;
		this->y /= n;
		this->z /= n;
		return *this;
	}
	
	double mag(){
		return sqrt(x*x + y*y + z*z);
	}
	
	double magSq(){
		return x*x + y*y + z*z;
	}
	
	double dist(const Vector& obj){
		Vector d = *this - obj;
		return d.mag();
	}
	
	Vector& normalize() {
		if (mag() == 0)
			return *this;
		*this/=mag();
		return *this;
	}
	
	Vector& limit(const double max){
		double mSq = this->magSq();
		if(mSq > max*max) {
			*this/=sqrt(mSq); //normalize it
			*this*=max;
		}
		return *this;
	}
	
	Vector& fromAngle(float angle) {
		return Vector(cos(angle),sin(angle),0);
	}
	
	Vector& random2D() {
		float angle;
		//if (this.p5._angleMode === constants.DEGREES) {
		  // angle = RandomF(360);
		// } else {
		  angle = RandomF(TWO_PI);
		// }
		return this->fromAngle(angle);
	}

	Vector& random3D() {
		float angle,vz;
		angle = RandomF(0,TWO_PI);
		vz = RandomF(-1,1);
		float vx = sqrt(1-vz*vz)*cos(angle);
		float vy = sqrt(1-vz*vz)*sin(angle);
		return Vector(vx,vy,vz);
	};
	
	friend ostream& operator<<(ostream& os,const Vector& obj){
		os << "(" << obj.x << ", " << obj.y << ", " <<  obj.z << ")";
		return os;
	}
};