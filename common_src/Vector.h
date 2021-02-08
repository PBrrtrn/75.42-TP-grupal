#ifndef __VECTOR_H__
#define __VECTOR_H__

struct Vector {
	Vector();
  Vector(float x, float y);
	Vector(float angle);
  ~Vector();
  float norm();
  void turnUnitary(); // TODO: Vector getUnit() sería mejor
  float getAngle();
  float getYCoordinate();
  float getXCoordinate();
  Vector operator*(float scalar);
  Vector operator+(const Vector &another);
  Vector operator-(const Vector &another);
  Vector& operator=(const Vector &another);
  bool operator==(const Vector& another);
  float x;
  float y;
};

#endif
