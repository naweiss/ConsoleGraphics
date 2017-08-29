#include <ostream>
using namespace std;

class Vector{
public:
	double x;
	double y;
	double z;
	
	Vector(double x = 0,double y = 0 , double z = 0);
	
	Vector(const Vector &obj);
	
	void set(double x = 0,double y = 0 , double z = 0);
	
	bool operator==(const Vector& obj);
	
	Vector operator+(const Vector& obj);
	
	Vector operator+=(const Vector& obj);
	
	Vector operator-(const Vector& obj);
	
	
	Vector operator-=(const Vector& obj);
	
	Vector operator*(const double n);
	
	Vector operator*=(const double n);
	
	Vector operator/(const double n);
	
	Vector operator/=(const double n);
	
	double mag();
	
	double magSq();
	
	double dist(const Vector& obj);
	
	Vector normalize();
	
	Vector limit(const double max);
	
	static Vector fromAngle(float angle);
	
	static Vector random2D();

	static Vector random3D();
	
	friend ostream& operator<<(ostream& os,const Vector& obj) {
	os << "(" << obj.x << ", " << obj.y << ", " <<  obj.z << ")";
	return os;
	}
};