#ifndef ROTATION3D_POLYGON_H
#define ROTATION3D_POLYGON_H

#include "GPlot.h"
#include "Vector.h"

const std::string COLOR = "#000000";
const int DEFAULT_LENGHT = 30;
const int AMOUT_OF_ANGLES = 4;
inline Gnuplot plt;

template<int SIZE = AMOUT_OF_ANGLES>
class Polygon {
private:
    std::array<Vector<STANDARD_SIZE>, SIZE> points;
    double edge_lenght;
    double AMOUT_OF_ANGLES;
    Vector<STANDARD_SIZE> cordinatesOfCenter;
    std::string colorRGB;
    std::string id;
public:
    Polygon(char axis = 'x');

    Polygon(int edge_lenght, char axis = 'x', std::string color = COLOR);

    Polygon(int edge_lenght, std::string color = COLOR, char axis = 'x');

    Polygon(std::array<Vector<STANDARD_SIZE>, SIZE> args) : points(args) {}

    Polygon(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> w, std::string color = COLOR);

    Polygon(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> w, Vector<STANDARD_SIZE> translationVector,
            std::string color = COLOR);

    void rotationAroundMainAxis(double x, double y, double z);

    void rotationAroundLocalAxis(double x, double y, double z);

    void rotationAroundMainAxis(Vector<STANDARD_SIZE> rotations);

    void rotationAroundLocalAxis(Vector<STANDARD_SIZE> rotations);

    void translation(Vector<STANDARD_SIZE> translationVector);

    void translation(double x, double y, double z);

    void draw();

    void setColor(std::string color);

    const Vector<STANDARD_SIZE> &operator[](int index) const;

    Vector<STANDARD_SIZE> &operator[](int index);
};

template<int SIZE>
Polygon<SIZE>::Polygon(char axis) {
    cordinatesOfCenter = Vector<STANDARD_SIZE>();
    edge_lenght = DEFAULT_LENGHT;
    AMOUT_OF_ANGLES = AMOUT_OF_ANGLES;
    colorRGB = COLOR;
    Vector v({0, 0, 0});
    switch (axis) {
        case 'x':
            v[0] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(0, 360 / AMOUT_OF_ANGLES, 0);
            }
            if (AMOUT_OF_ANGLES == AMOUT_OF_ANGLES) rotationAroundMainAxis(0, 45, 0);
            break;
        case 'y':
            v[1] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(0, 0, 360 / AMOUT_OF_ANGLES);
            }
            if (AMOUT_OF_ANGLES == AMOUT_OF_ANGLES) rotationAroundMainAxis(0, 0, 45);
            break;
        case 'z':
            v[2] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(360 / AMOUT_OF_ANGLES, 0, 0);
            }
            if (AMOUT_OF_ANGLES == AMOUT_OF_ANGLES) rotationAroundMainAxis(45, 0, 0);
            break;
    }

}

template<int SIZE>
Polygon<SIZE>::Polygon(int edge_lenght, char axis, std::string color) {
    cordinatesOfCenter = Vector<STANDARD_SIZE>();
    this->edge_lenght = edge_lenght;
    AMOUT_OF_ANGLES = SIZE;
    this->colorRGB = color;
    Vector v({0, 0, 0});
    switch (axis) {
        case 'x':
            v[0] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(0, 360 / AMOUT_OF_ANGLES, 0);
            }
            if (AMOUT_OF_ANGLES == AMOUT_OF_ANGLES) rotationAroundMainAxis(0, 45, 0);
            break;
        case 'y':
            v[1] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(360 / AMOUT_OF_ANGLES, 0, 0);
            }
            if (AMOUT_OF_ANGLES == AMOUT_OF_ANGLES) rotationAroundMainAxis(45, 0, 0);
            break;
        case 'z':
            v[2] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(360 / AMOUT_OF_ANGLES, 0, 0);
            }
            if (AMOUT_OF_ANGLES == AMOUT_OF_ANGLES) rotationAroundMainAxis(45, 0, 0);
            break;
    }
}

template<int SIZE>
Polygon<SIZE>::Polygon(int edge_lenght, std::string color, char axis) {
    cordinatesOfCenter = Vector<STANDARD_SIZE>();
    this->edge_lenght = edge_lenght;
    AMOUT_OF_ANGLES = SIZE;
    this->colorRGB = color;
    Vector v({0, 0, 0});
    switch (axis) {
        case 'x':
            v[0] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(0, 360 / AMOUT_OF_ANGLES, 0);
            }
            if (AMOUT_OF_ANGLES == AMOUT_OF_ANGLES) rotationAroundMainAxis(0, 45, 0);
            break;
        case 'y':
            v[1] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(360 / AMOUT_OF_ANGLES, 0, 0);
            }
            if (AMOUT_OF_ANGLES == AMOUT_OF_ANGLES) rotationAroundMainAxis(45, 0, 0);
            break;
        case 'z':
            v[2] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(360 / AMOUT_OF_ANGLES, 0, 0);
            }
            if (AMOUT_OF_ANGLES == AMOUT_OF_ANGLES) rotationAroundMainAxis(45, 0, 0);
            break;
    }
}

template<int SIZE>
void Polygon<SIZE>::draw() {
    if (id.empty()) {
        id = "P#" + std::to_string(plt.listOfObject.size() + 1);
    }

    std::stringstream tmp, command;
    tmp << "from " << points[0][0] << "," << points[0][2] << "," << points[0][1] << " to ";
    for (int i = 1; i < SIZE; ++i) {
        tmp << points[i][0] << "," << points[i][2] << "," << points[i][1] << " to ";
    }
    tmp << points[0][0] << "," << points[0][2] << "," << points[0][1];

    if (plt.listOfObject.find(id) == plt.listOfObject.end()) {
        plt.listOfObject[id] = plt.listOfObject.size() + 1;
    }
    command << "set object " << plt.listOfObject[id] << " polygon " << tmp.str() <<
            " fillstyle transparent solid fillcolor rgb \"" << colorRGB << "\"";

    plt.sendcommand(command.str());
}

template<int SIZE>
void Polygon<SIZE>::rotationAroundMainAxis(double x, double y, double z) {
    for (int i = 0; i < SIZE; ++i) {
        points[i].rotateByEulerAngles(x, y, z);
    }
}

template<int SIZE>
void Polygon<SIZE>::translation(Vector<STANDARD_SIZE> translationVector) {
    cordinatesOfCenter = cordinatesOfCenter + translationVector;
    for (int i = 0; i < SIZE; ++i) {
        points[i].translation(translationVector);
    }
}

template<int SIZE>
void Polygon<SIZE>::rotationAroundLocalAxis(double x, double y, double z) {
    Vector<STANDARD_SIZE> vec = cordinatesOfCenter;
    vec = vec * -1;
    translation(vec);
    rotationAroundMainAxis(x, y, z);
    vec = vec * -1;
    translation(vec);
}

template<int SIZE>
void Polygon<SIZE>::translation(double x, double y, double z) {
    Vector<STANDARD_SIZE> vectorTranslation({x, y, z});
    translation(vectorTranslation);
}

template<int SIZE>
Polygon<SIZE>::Polygon(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> w, std::string color) {
    if (color.length() != 7 || color[0] != '#') throw std::invalid_argument("Unknow rgb format!");
    points[0] = Vector({0, 0, 0});
    points[1] = v;
    points[2] = v + w;
    points[3] = w;
    colorRGB = color;
    //TODO SPRAWDZIC
    double x = distanceBetweenTwoVectors(points[0], points[1]);
    double y = distanceBetweenTwoVectors(points[3], points[0]);
    double z = distanceBetweenTwoVectors(points[2], points[0]);
    cordinatesOfCenter = Vector<STANDARD_SIZE>({x, y, z});
}

template<int SIZE>
Polygon<SIZE>::Polygon(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> w, Vector<STANDARD_SIZE> translationVector,
                       std::string color) {
    if (color.length() != 7 || color[0] != '#') throw std::invalid_argument("Unknow rgb format!");
    points[0] = Vector({0, 0, 0});
    points[1] = v;
    points[2] = v + w;
    points[3] = w;
    colorRGB = color;
    translation(translationVector);
    double x = distanceBetweenTwoVectors(points[0], points[1]);
    double y = distanceBetweenTwoVectors(points[3], points[0]);
    double z = distanceBetweenTwoVectors(points[2], points[0]);
    cordinatesOfCenter = Vector<STANDARD_SIZE>({x, y, z});
}

template<int SIZE>
const Vector<STANDARD_SIZE> &Polygon<SIZE>::operator[](int index) const {
    if (index >= SIZE || index < 0) throw std::invalid_argument("Index out of range!");
    return points[index];
}

template<int SIZE>
Vector<STANDARD_SIZE> &Polygon<SIZE>::operator[](int index) {
    if (index >= SIZE || index < 0) throw std::invalid_argument("Index out of range!");
    return points[index];
}

template<int SIZE>
void Polygon<SIZE>::rotationAroundMainAxis(Vector<STANDARD_SIZE> rotations) {
    rotationAroundMainAxis(rotations[0], rotations[1], rotations[2]);
}

template<int SIZE>
void Polygon<SIZE>::rotationAroundLocalAxis(Vector<STANDARD_SIZE> rotations) {
    rotationAroundLocalAxis(rotations[0], rotations[1], rotations[2]);
}

template<int SIZE>
void Polygon<SIZE>::setColor(std::string color) {
    colorRGB = color;
}

template<int SIZE>
std::ostream &operator<<(std::ostream &ost, const Polygon<SIZE> &pol) {
    ost << std::setprecision(STREAM_PRECISION) << std::fixed;

    for (int i = 0; i < SIZE; ++i) {
        ost  << "[" << pol[i] << "] ";
    }

    return ost;
}

#endif //ROTATION3D_POLYGON_H
