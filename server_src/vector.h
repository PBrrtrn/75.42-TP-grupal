#ifndef VECTOR_H
#define VECTOR_H


class Vector {

public:
    Vector();
    Vector(float x, float y);
    Vector(float angle);
    ~Vector();
    float calculateNorma();
    void turnUnitary();
    void turnUnitaryVerbose();
    float getAngle();
    float getYCoordinate();
    float getXCoordinate();
    Vector operator*(float scalar);
    Vector operator+(const Vector &another);
    Vector& operator=(const Vector &another);

private:
    float x;
    float y;

};

#endif
