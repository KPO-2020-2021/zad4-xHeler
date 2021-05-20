#include "Cuboid.h"


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
    cordinatesOfCenter = cordinatesOfCenter + translationVector;
    for (int i = 0; i < AMOUNT_OF_WALLS; ++i) {
        walls[i].translation(translationVector);
    }
}

void Cuboid::rotationAroundMainAxis(double x, double y, double z) {
    cordinatesOfCenter.rotateByEulerAngles(x, y, z);
    for (int i = 0; i < AMOUNT_OF_WALLS; ++i) {
        walls[i].rotationAroundMainAxis(x, y, z);
    }
}

void Cuboid::rotationAroundLocalAxis(double x, double y, double z) {
    Vector<STANDARD_SIZE> tmp = cordinatesOfCenter * -1;
    translation(tmp);
    rotationAroundMainAxis(x, y, z);
    translation(tmp * -1);
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
    for (int i = 0; i < AMOUNT_OF_WALLS; ++i) {
        walls[i].draw();
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