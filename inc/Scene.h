#ifndef ROTATION3D_SCENE_H
#define ROTATION3D_SCENE_H

#include "Cuboid.h"

const int FPS = 60;

class Scene{
private:
    Cuboid cuboid;
    Vector<STANDARD_SIZE> rotation;
    Vector<STANDARD_SIZE> rotationPrevious;
    std::vector<Vector<STANDARD_SIZE>> rotationsSequence;
    Vector<STANDARD_SIZE> translation;
    Vector<STANDARD_SIZE> translationTotal;
public:
    Scene();

    void setRotation();
    void setTranslation();
    void setPreviousRotation();
    void displayRotationMatrix();
    void displayPoints();
    void displayLenght();
    void animate(int numerOfOperations = FPS);
};

#endif //ROTATION3D_SCENE_H
