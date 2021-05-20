#ifndef ROTATION3D_CUBOID_H
#define ROTATION3D_CUBOID_H

#include "Polygon.h"
#include <vector>

extern Gnuplot plt;
const int AMOUNT_OF_WALLS = 6;

class Cuboid {
private:
    std::array<Polygon<AMOUT_OF_ANGLES>, AMOUNT_OF_WALLS> walls;
    Vector<STANDARD_SIZE> cordinatesOfCenter;
public:
    Cuboid();

    Cuboid(double size, std::string color = COLOR);

    Cuboid(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> r, Vector<STANDARD_SIZE> w,
           Vector<STANDARD_SIZE> translationVector = Vector<STANDARD_SIZE>(),
           std::string color = COLOR);


    void translation(double x, double y, double z);

    void translation(Vector<STANDARD_SIZE> translationVector);

    void rotationAroundMainAxis(double x, double y, double z);

    void rotationAroundLocalAxis(double x, double y, double z);

    void rotationUsingSequence(std::vector<Vector<STANDARD_SIZE>> sequence);

    const Polygon<AMOUT_OF_ANGLES> &operator[](int index) const;

    Polygon<AMOUT_OF_ANGLES> &operator[](int index);

    void draw();
    void showLenght();
    void setColor(std::string color);

};

std::ostream &operator<<(std::ostream &ost, const Cuboid &cub);


#endif //ROTATION3D_CUBOID_H
