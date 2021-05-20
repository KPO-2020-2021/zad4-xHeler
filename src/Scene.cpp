#include <thread>
#include "Scene.h"

Scene::Scene() {
    cuboid = Cuboid(30);
    rotation = Vector();
    rotationPrevious = Vector();
    translation = Vector();
    translationTotal = Vector();
}

void Scene::setRotation() {
    char axis = ' ';
    double angel = 0;

    while (axis != '.') {
        std::cout << "Enter axis:";
        if(!(std::cin >> axis)) {
            std::cout << "You must insert only one char and press enter!\n";
            throw std::invalid_argument("Input error! Must be char!");
        }

        std::cout << "Enter angle:";
        if(!(std::cin >> angel)) {
            std::cout << "You must insert number!\n";
            throw std::invalid_argument("Input error! Must be number!");
        }

        switch (axis) {
            case 'x':
                rotation = Vector({angel, 0, 0});
                rotationsSequence.push_back(rotation);
                break;
            case 'y':
                rotation = Vector({0, angel, 0});
                rotationsSequence.push_back(rotation);
                break;
            case 'z':
                rotation = Vector({0, 0, angel});
                rotationsSequence.push_back(rotation);
                break;
            default:
                break;
        }
    }
}

void Scene::setPreviousRotation() {
    rotationsSequence.push_back(rotationsSequence[rotationsSequence.size() - 1]);
}

void Scene::setTranslation() {
    std::cin >> translation;
}

void Scene::displayRotationMatrix() {

    rotation = rotationsSequence[rotationsSequence.size() - 1];

    double angle = 0;
    angle = (M_PI / 180) * rotation[0];
    Quaternion q_x(std::cos(angle / 2), std::sin(angle / 2), 0, 0);
    std::cout << "Macierz X" << std::endl;
    std::cout <<  q_x.getRotationMatrix();

    angle = (M_PI / 180) * rotation[1];
    Quaternion q_y(std::cos(angle / 2), 0, std::sin(angle / 2), 0);
    std::cout << "Macierz Y" << std::endl;
    std::cout << q_y.getRotationMatrix();

    angle = (M_PI / 180) * rotation[1];
    Quaternion q_z(std::cos(angle / 2), 0, 0, std::sin(angle / 2));
    std::cout << "Macierz Z" << std::endl;
    std::cout << q_z.getRotationMatrix();

}

void Scene::displayPoints() {
    Cuboid copy = cuboid;

    copy.translation(translationTotal);
    copy.rotationUsingSequence(rotationsSequence);

    std::cout << cuboid << std::endl;
}

void Scene::displayLenght() {
    cuboid.showLenght();
}

void Scene::animate(int numerOfOperations) {
    cuboid.draw();
    Cuboid copy = cuboid;
    Vector translationTmp = translation / numerOfOperations;

    for (int i = 0; i < rotationsSequence.size(); ++i) {
        rotationsSequence[i] = rotationsSequence[i] / numerOfOperations;
    }

    copy.translation(translationTotal);

    for (int i = 0; i < numerOfOperations; ++i) {
        translationTotal = translationTotal + translationTmp;
        copy.translation(translationTotal);
        copy.rotationUsingSequence(rotationsSequence);
        cuboid.rotationUsingSequence(rotationsSequence);
        copy.draw();
        plt.initializePlot3D();
        copy = cuboid;
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / FPS));
        plt.initializePlot3D();
    }

    rotationPrevious = rotation;
    rotation = Vector();
    translation = Vector();
}


