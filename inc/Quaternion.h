#ifndef ROTATIONS3D_QUATERNION_H
#define ROTATIONS3D_QUATERNION_H

#include "Matrix.h"
#include <iostream>

const int PRECISION = 10;
const int MATRIX_SIZE = 3;

class Quaternion {
private:
    double W;
    double X;
    double Y;
    double Z;

public:
    Quaternion();
    Quaternion(double w, double x, double y, double z);
    Matrix<MATRIX_SIZE> getRotationMatrix();

    friend std::ostream & operator<<(std::ostream & ost, const Quaternion &qua);
    Quaternion operator+(const Quaternion & q);
    Quaternion operator*(const Quaternion & q);
    void conjugate();
    Quaternion getConjugate();

    double getW() const;

    void setW(double w);

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getZ() const;

    void setZ(double z);
};

#endif //ROTATIONS3D_QUATERNION_H
