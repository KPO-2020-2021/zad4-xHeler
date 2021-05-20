#ifndef ROTATION3D_SCENE_H
#define ROTATION3D_SCENE_H

#include "Cuboid.h"

class Scene{
private:
    Cuboid cuboid;
    Vector<STANDARD_SIZE> rotation;
    Vector<STANDARD_SIZE> rotationPrevious;
    std::vector<Vector<STANDARD_SIZE>> rotationsTotal;
    Vector<STANDARD_SIZE> translation;
    Vector<STANDARD_SIZE> translationTotal;
public:
    Scene();

    void setRotationSequence();
    void setTranslation();
    void setPreviousRotation();
    void displayRotationMatrix();
    void displayVerticies();
    void displayLenght();
    void animate(int numerOfOperations);
};

#endif //ROTATION3D_SCENE_H
