#ifndef ROTATION3D_POLYGON_H
#define ROTATION3D_POLYGON_H

#include "Plot.h"
#include "Vector.h"

const std::string COLOR = "#000000";
const int DEFAULT_LENGHT = 30;
const int ANGLES = 4;
extern Gnuplot plt;

template<int SIZE = ANGLES>
class Polygon {
private:
    std::array<Vector<STANDARD_SIZE>, SIZE> points;
    double edge_lenght;
    double angles;
    Vector<STANDARD_SIZE> cordinatesOfCenter;
    std::string colorRGB;
    std::string id;
public:
    Polygon(char axis = 'x');
    Polygon(int edge_lenght, char axis = 'x', std::string color = COLOR);
    Polygon(int edge_lenght, std::string color = COLOR, char axis = 'x');
    Polygon(std::array<Vector<STANDARD_SIZE>, SIZE> args) : points(args){}

    void rotationAroundMainAxis(double x, double y, double z);
    void rotationAroundLocalAxis(double x, double y, double z);
    void translation(Vector<STANDARD_SIZE> tranlationVector);
    void translation(double x, double y, double z);
    void draw();
};

template<int SIZE>
Polygon<SIZE>::Polygon(char axis) {
    cordinatesOfCenter = Vector<STANDARD_SIZE>();
    edge_lenght = DEFAULT_LENGHT;
    angles = ANGLES;
    colorRGB = COLOR;
    Vector v({0, 0, 0});
    switch (axis) {
        case 'x':
            v[0] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(0, 360 / angles, 0);
            }
            if (angles == ANGLES) rotationAroundMainAxis(0, 45, 0);
            break;
        case 'y':
            v[1] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(0, 0, 360 / angles);
            }
            if (angles == ANGLES) rotationAroundMainAxis(0, 0, 45);
            break;
        case 'z':
            v[2] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(360 / angles, 0, 0);
            }
            if (angles == ANGLES) rotationAroundMainAxis(45, 0, 0);
            break;
    }

}

template<int SIZE>
Polygon<SIZE>::Polygon(int edge_lenght, char axis, std::string color) {
    cordinatesOfCenter = Vector<STANDARD_SIZE>();
    this->edge_lenght = edge_lenght;
    angles = SIZE;
    this->colorRGB = color;
    Vector v({0, 0, 0});
    switch (axis) {
        case 'x':
            v[0] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(0, 360 / angles, 0);
            }
            if (angles == ANGLES) rotationAroundMainAxis(0, 45, 0);
            break;
        case 'y':
            v[1] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(360 / angles, 0, 0);
            }
            if (angles == ANGLES) rotationAroundMainAxis(45, 0, 0);
            break;
        case 'z':
            v[2] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(360 / angles, 0, 0);
            }
            if (angles == ANGLES) rotationAroundMainAxis(45, 0, 0);
            break;
    }
}

template<int SIZE>
Polygon<SIZE>::Polygon(int edge_lenght, std::string color, char axis) {
    cordinatesOfCenter = Vector<STANDARD_SIZE>();
    this->edge_lenght = edge_lenght;
    angles = SIZE;
    this->colorRGB = color;
    Vector v({0, 0, 0});
    switch (axis) {
        case 'x':
            v[0] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(0, 360 / angles, 0);
            }
            if (angles == ANGLES) rotationAroundMainAxis(0, 45, 0);
            break;
        case 'y':
            v[1] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(360 / angles, 0, 0);
            }
            if (angles == ANGLES) rotationAroundMainAxis(45, 0, 0);
            break;
        case 'z':
            v[2] = edge_lenght;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = v;
                v.rotateByEulerAngles(360 / angles, 0, 0);
            }
            if (angles == ANGLES) rotationAroundMainAxis(45, 0, 0);
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
void Polygon<SIZE>::translation(Vector<STANDARD_SIZE> tranlationVector) {
    cordinatesOfCenter = cordinatesOfCenter + tranlationVector;
    for (int i = 0; i < SIZE; ++i) {
        points[i].translation(tranlationVector);
    }
}

template<int SIZE>
void Polygon<SIZE>::rotationAroundLocalAxis(double x, double y, double z) {
    Vector<STANDARD_SIZE> vec = cordinatesOfCenter;
    Vector<STANDARD_SIZE> returned = cordinatesOfCenter;
    vec = vec * -1;+
    translation(vec);
    rotationAroundMainAxis(x, y, z);
    translation(returned);
}

template<int SIZE>
void Polygon<SIZE>::translation(double x, double y, double z) {
    Vector<STANDARD_SIZE> vectorTranslation({x, y, z});
    translation(vectorTranslation);
}

#endif //ROTATION3D_POLYGON_H
