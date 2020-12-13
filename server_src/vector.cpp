#include "vector.h"
#include <math.h>
#include <iostream>

Vector::Vector() {}

Vector::Vector(float x, float y) : x(x), y(y){}

Vector::~Vector() {}

Vector& Vector::operator=(const Vector &another){
    this->x = another.x;
    this->y = another.y;
    return *this;
}

void Vector::turnUnitary() {
    float norma = calculateNorma();
    this->x = this->x / norma;
    this->y = this->y / norma;
}

void Vector::turnUnitaryVerbose() {
    std::cout << "Before unitary: " <<std::endl;
    std::cout <<"dir coord x: " << this->x << std::endl;
    std::cout <<"dir coord y: " << this->y << std::endl;
    std::cout << "Calculating: " <<std::endl;
    float norma = calculateNorma();
    std::cout << "norma: "<<norma <<std::endl;
    std::cout << "new x: "<<this->x / norma <<std::endl;
    std::cout << "new y: " <<this->y / norma <<std::endl;
    this->x = this->x / norma;
    this->y = this->y / norma;
}

float Vector::calculateNorma() {
    return sqrt((this->x * this->x) + (this->y * this->y));
}

float Vector::getAngle() {
    /*std::cout << "Get angle function" << std::endl;
    std::cout << "x: " << this->x << " y: " << this->y << std::endl;*/
    return atan2(this->y, this->x);
    //return atan(this->y / this->x);
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

Vector Vector::operator+(const Vector &another) {
    return Vector(this->x + another.x, this->y + another.y);
}

Vector::Vector(float angle) {
    /*std::cout << "ANGLE 3: " << angle << std::endl;*/
    this->x = cos(angle);
    this->y = sin(angle);
    /*if (cos(angle) == 0){
        this->y = sin(angle) > 0 ? 1 : -1;
        this->x = this->y / tan(angle);
    } else{
        std::cout << "ENTRA ACAAAAA 3: " << angle << std::endl;
        this->x = cos(angle) > 0 ? 1 : -1;
        this->y = tan(angle) * this->x;
    }*/

}