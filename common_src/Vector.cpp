#include <math.h>

#include "Vector.h"

Vector::Vector() { }

Vector::Vector(float x, float y) : x(x), y(y) { }

Vector::Vector(float angle) {
	this->x = cos(angle);
	this->y = sin(angle);
}

Vector::~Vector() { }

float Vector::norm() {
  return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

void Vector::turnUnitary() { 
	// TODO: Vector getUnit() sería mejor
	float norm = this->norm();
	this->x = (this->x)/(norm);
	this->y = (this->y)/(norm);
}

float Vector::getAngle() {
  return atan2(this->y, this->x);
}

float Vector::getXCoordinate() {
  return this->x;
}

float Vector::getYCoordinate() {
  return this->y;
}

Vector Vector::operator*(float scalar) {
  return Vector(this->x * scalar, this->y * scalar);
}

Vector Vector::operator+(const Vector& another) {
  return Vector(this->x + another.x, this->y + another.y);
}

Vector& Vector::operator=(const Vector& another){
  this->x = another.x;
  this->y = another.y;
  return *this;
}
