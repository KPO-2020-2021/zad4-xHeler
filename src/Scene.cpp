#include "Scene.h"

Scene::Scene() {
    cuboid = Cuboid(30, "#00FF00");
    rotation = Vector();
    rotationPrevious = Vector();
    translation = Vector();
    translationTotal = Vector();
}

void Scene::setRotationSequence() {//TODO NEED TEST!
    char axis = ' ';
    double angel = 0;
    Vector rotation;

    while (axis != '.') {
        while(!(std::cin >> axis)) { //!TODO TEST
            std::cout << "You must insert only one char and press enter!\n";
            throw std::invalid_argument("Input error! Must be char!");
        }
        axis = tolower(axis);
        if (axis != 'x' || axis != 'y' ||  axis != 'z') std::cout << "Wrong axis ! Possible axis: |x, y, z|\n";

        while(!(std::cin >> angel)) { //!TODO TEST
            std::cout << "You must insert number!\n";
            throw std::invalid_argument("Input error! Must be number!");
        }

        switch (axis) {
            case 'x':
                rotation = Vector({angel, 0, 0});
                break;
            case 'y':
                rotation = Vector({0, angel, 0});
                break;
            case 'z':
                rotation = Vector({0, 0, angel});
                break;
            default:
                break;
        }
    }
}

void Scene::setPreviousRotation() {
    rotation = rotationPrevious;
}

void Scene::setTranslation() {
    std::cout << "Enter translation vector: ";
    std::cin >> translation;
}

void Scene::displayRotationMatrix() {
    double angle = 0;
    if (rotation[0] != 0) {
        angle = (M_PI / 180) * rotation[0];
         Quaternion q_x(std::cos(angle / 2), std::sin(angle / 2), 0, 0);
         std::cout << q_x.getRotationMatrix();
    }

    if (rotation[1] != 0) {
        angle = (M_PI / 180) * rotation[1];
        Quaternion q_y(std::cos(angle / 2), 0, std::sin(angle / 2), 0);
        std::cout << q_y.getRotationMatrix();
    }

    if (rotation[1] != 0) {
        angle = (M_PI / 180) * rotation[1];
        Quaternion q_z(std::cos(angle / 2), 0, 0, std::sin(angle / 2));
        std::cout << q_z.getRotationMatrix();
    }
}

void Scene::displayVerticies() {
    Cuboid copy = cuboid;

    copy.translation(translationTotal);
    copy.rotationUsingSequence(rotationsTotal);

    std::cout << cuboid << std::endl;
}

void Scene::displayLenght() {
    cuboid.showLenght();
}

void Scene::animate(int numerOfOperations) {
    Cuboid copy = cuboid;
    Vector translationTmp = translation / numerOfOperations;

    copy.translation(translationTotal);
    copy.rotationUsingSequence(rotationsTotal);
}
