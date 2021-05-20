#ifndef ROTATION3D_CUBOID_H
#define ROTATION3D_CUBOID_H

#include "Polygon.h"
#include <vector>

const int AMOUNT_OF_WALLS = 6;

class Cuboid {
private:
    std::array<Polygon<AMOUT_OF_ANGLES>, AMOUNT_OF_WALLS> walls;
    Vector<STANDARD_SIZE> cordinatesOfCenter;
    std::vector<Vector<STANDARD_SIZE>> rotationsMain;
    std::vector<Vector<STANDARD_SIZE>> rotationsLocal;
    Vector<STANDARD_SIZE> movement;
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

Cuboid::Cuboid() {

}

Cuboid::Cuboid(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> r, Vector<STANDARD_SIZE> w,
               Vector<STANDARD_SIZE> translationVector, std::string color) {
    walls[0] = Polygon(w, v);
    walls[1] = Polygon(w, v, r);
    walls[2] = Polygon(r, w);
    walls[3] = Polygon(r, v, w);
    walls[4] = Polygon(r, w, v);
    walls[5] = Polygon(r, v);

    double x = distanceBetweenTwoVectors(walls[0][0], walls[0][3]) / 2;
    double y = distanceBetweenTwoVectors(walls[0][0], walls[1][0]) / 2;
    double z = distanceBetweenTwoVectors(walls[0][0], walls[0][1]) / 2;
    cordinatesOfCenter = Vector<STANDARD_SIZE>({x, y, z});
    setColor(color);
}


void Cuboid::translation(double x, double y, double z) {
    translation(Vector<STANDARD_SIZE>({x, y, z}));
}

void Cuboid::translation(Vector<STANDARD_SIZE> translationVector) {
    movement = movement + translationVector;
    cordinatesOfCenter = cordinatesOfCenter + translationVector;
}

void Cuboid::rotationAroundMainAxis(double x, double y, double z) {
    rotationsMain.push_back(Vector<STANDARD_SIZE>({x, y, z}));
    cordinatesOfCenter.rotateByEulerAngles(x, y, z);
}

void Cuboid::rotationAroundLocalAxis(double x, double y, double z) {
    rotationsLocal.push_back(Vector<STANDARD_SIZE>({x, y, z}));
}

const Polygon<AMOUT_OF_ANGLES> &Cuboid::operator[](int index) const {
    if (index > STANDARD_SIZE || index < 0) throw std::out_of_range("Index ?!");
    return walls[index];
}

Polygon<AMOUT_OF_ANGLES> &Cuboid::operator[](int index) {
    if (index > STANDARD_SIZE || index < 0) throw std::out_of_range("Index ?!");
    return walls[index];
}

void Cuboid::draw() {
    std::array<Polygon<AMOUT_OF_ANGLES>, AMOUNT_OF_WALLS> wallsCOPY = walls;

    for (int i = 0; i < AMOUNT_OF_WALLS; ++i) {
        wallsCOPY[i].translation(movement);
    }

    for (int i = 0; i < AMOUNT_OF_WALLS; ++i) {
        for (int j = 0; j < rotationsMain.size(); ++j) {
            wallsCOPY[i].rotationAroundMainAxis(rotationsMain[j]);
        }
    }


    for (int i = 0; i < AMOUNT_OF_WALLS; ++i) {
        for (int j = 0; j < rotationsLocal.size(); ++j) {
            Vector<STANDARD_SIZE> tmp = cordinatesOfCenter * -1;
            wallsCOPY[i].translation(tmp);
            wallsCOPY[i].rotationAroundMainAxis(rotationsLocal[j]);
            wallsCOPY[i].translation(tmp * -1);
        }
    }

    for (int i = 0; i < AMOUNT_OF_WALLS; ++i) {
        wallsCOPY[i].draw();
    }
}

void Cuboid::showLenght() {
    double x = distanceBetweenTwoVectors(walls[0][0], walls[0][3]);
    double y = distanceBetweenTwoVectors(walls[0][0], walls[1][0]);
    double z = distanceBetweenTwoVectors(walls[0][0], walls[0][1]);
    std::cout << "Wielkość graniastoslupa to: " << x << " x " << y << " x " << z << std::endl;
    std::cout << "Podstawa: " << x << " x " << z << std::endl;
    std::cout << "Wysokosc: " << y << std::endl;
}

Cuboid::Cuboid(double size, std::string color) {
    Vector<3> v({size, 0, 0});
    Vector<3> r({0, size, 0});
    Vector<3> w({0, 0, size});
    walls[0] = Polygon(w, v);
    walls[1] = Polygon(w, v, r);
    walls[2] = Polygon(r, w);
    walls[3] = Polygon(r, v, w);
    walls[4] = Polygon(r, w, v);
    walls[5] = Polygon(r, v);

    double x = distanceBetweenTwoVectors(walls[0][0], walls[0][3]) / 2;
    double y = distanceBetweenTwoVectors(walls[0][0], walls[1][0]) / 2;
    double z = distanceBetweenTwoVectors(walls[0][0], walls[0][1]) / 2;
    cordinatesOfCenter = Vector<STANDARD_SIZE>({x, y, z});
    setColor(color);
}

void Cuboid::setColor(std::string color) {
    for (int i = 0; i < AMOUNT_OF_WALLS; ++i) {
        walls[i].setColor(color);
    }
}

void Cuboid::rotationUsingSequence(std::vector<Vector<STANDARD_SIZE>> sequence) {
    for (int i = 0; i < sequence.size(); ++i) {
        rotationAroundMainAxis(sequence[i][0], sequence[i][1], sequence[i][2]);
    }
}


std::ostream &operator<<(std::ostream &ost, const Cuboid &cub) {
    ost << std::setprecision(STREAM_PRECISION) << std::fixed;

    for (int i = 0; i < AMOUNT_OF_WALLS; ++i) {
        ost << "Wall [" << i + 1 << "]: " << cub[i] << std::endl;
    }

    return ost;
}


#endif //ROTATION3D_CUBOID_H
