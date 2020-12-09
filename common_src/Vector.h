//
// Created by alejo on 25/11/20.
//

#ifndef PRUEBA_SDL_VECTOR_H
#define PRUEBA_SDL_VECTOR_H


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


#endif //PRUEBA_SDL_VECTOR_H
