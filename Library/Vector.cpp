#include "Maths.h"
#include "Vector.h"

Vector::Vector(double x,double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::Vector(const Vector &obj) {
	this->x = obj.x;
	this->y = obj.y;
	this->z = obj.z;
}

void Vector::set(double x,double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

bool Vector::operator==(const Vector& obj){
	return ((x == obj.x) && (y == obj.y) && (z == obj.z));
}

Vector Vector::operator+(const Vector& obj){
	Vector result;
	result.x = this->x + obj.x;
	result.y = this->y + obj.y;
	result.z = this->z + obj.z;
	return result;
}

Vector Vector::operator+=(const Vector& obj){
	this->x += obj.x;
	this->y += obj.y;
	this->z += obj.z;
	return *this;
}

Vector Vector::operator-(const Vector& obj){
	Vector result;
	result.x = this->x - obj.x;
	result.y = this->y - obj.y;
	result.z = this->z - obj.z;
	return result;
}


Vector Vector::operator-=(const Vector& obj){
	this->x -= obj.x;
	this->y -= obj.y;
	this->z -= obj.z;
	return *this;
}

Vector Vector::operator*(const double n){
	Vector result;
	result.x = this->x * n;
	result.y = this->y * n;
	result.z = this->z * n;
	return result;
}


Vector Vector::operator*=(const double n){
	this->x *= n;
	this->y *= n;
	this->z *= n;
	return *this;
}

Vector Vector::operator/(const double n){
	Vector result;
	result.x = this->x / n;
	result.y = this->y / n;
	result.z = this->z / n;
	return result;
}


Vector Vector::operator/=(const double n){
	this->x /= n;
	this->y /= n;
	this->z /= n;
	return *this;
}

double Vector::mag(){
	return sqrt(x*x + y*y + z*z);
}

double Vector::magSq(){
	return x*x + y*y + z*z;
}

double Vector::dist(const Vector& obj){
	Vector d = *this - obj;
	return d.mag();
}

Vector Vector::normalize() {
	if (mag() == 0)
		return *this;
	*this/=mag();
	return *this;
}

Vector Vector::limit(const double max){
	double mSq = this->magSq();
	if(mSq > max*max) {
		*this/=sqrt(mSq); //normalize it
		*this*=max;
	}
	return *this;
}

Vector Vector::fromAngle(float angle) {
	return Vector(cos(angle),sin(angle),0);
}

Vector Vector::random2D() {
	float angle = RandomF(TWO_PI);
	return fromAngle(angle);
}

Vector Vector::random3D() {
	float angle,vz;
	angle = RandomF(0,TWO_PI);
	vz = RandomF(-1,1);
	float vx = sqrt(1-vz*vz)*cos(angle);
	float vy = sqrt(1-vz*vz)*sin(angle);
	return Vector(vx,vy,vz);
};