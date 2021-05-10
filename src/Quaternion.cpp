#include <iomanip>
#include "Quaternion.h"

Quaternion::Quaternion() {
    this->W = 1;
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
}

Quaternion::Quaternion(double w, double x, double y, double z) {
    this->W = w;
    this->X = x;
    this->Y = y;
    this->Z = z;
}

Matrix<MATRIX_SIZE> Quaternion::getRotationMatrix() {
    double A = 1 - 2 * Y * Y - 2 * Z * Z;
    double B = 2 * X * Y - 2 * Z * W;
    double C = 2 * X * Z + 2 * Y * W;
    double D = 2 * X * Y + 2 * Z * W;
    double E = 1 - 2 * X * X - 2 * Z * Z;
    double F = 2 * Y * Z - 2 * X * W;
    double G = 2 * X * Z - 2 * Y * W;
    double H = 2 * Y * Z + 2 * X * W;
    double I = 1 - 2 * X * X - 2 * Y * Y;
    return Matrix<MATRIX_SIZE>({A,B,C,D,E,F,G,H,I});
}

double Quaternion::getW() const {
    return W;
}

void Quaternion::setW(double w) {
    W = w;
}

double Quaternion::getX() const {
    return X;
}

void Quaternion::setX(double x) {
    X = x;
}

double Quaternion::getY() const {
    return Y;
}

void Quaternion::setY(double y) {
    Y = y;
}

double Quaternion::getZ() const {
    return Z;
}

void Quaternion::setZ(double z) {
    Z = z;
}

Quaternion Quaternion::operator+(const Quaternion &v) {
    return Quaternion(getW() + v.getW(), getX() + v.getX(), getY() + v.getY(), getZ() + v.getZ());
}

std::ostream &operator<<(std::ostream &ost, const Quaternion &qua) {
    std::cout << std::fixed;
    std::cout << std::setprecision(PRECISION);
    ost << qua.getW() << ",";
    ost << qua.getX() << ",";
    ost << qua.getY() << ",";
    ost << qua.getZ();

    return ost;
}

Quaternion Quaternion::operator*(const Quaternion &q) {
    return Quaternion(W * q.W - X * q.X - Y * q.Y - Z * q.Z,
                      W * q.X + X * q.W + Y * q.Z - Z * q.Y,
                      W * q.Y - X * q.Z + Y * q.W + Z * q.X,
                      W * q.Z + X * q.Y - Y * q.X + Z * q.W);
}

void Quaternion::conjugate() {
    X = -X;
    Y = -Y;
    Z = -Z;
}

Quaternion Quaternion::getConjugate() {
    Quaternion tmp(W, X, Y, Z);
    tmp.conjugate();
    return tmp;
}



