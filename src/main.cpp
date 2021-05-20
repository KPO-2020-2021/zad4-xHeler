#include "Scene.h"

void displayMenu();

int main() {
    Scene scene;
    char option = ' ';
    int amountOfRotations = 1;

    displayMenu();
    do {
        std::cout << "Enter option:";
        std::cin >> option;

        switch (option) {
            case 'r':
                scene.setRotation();
                std::cout << "Enter amount of rotations: ";
                std::cin >> amountOfRotations;
                scene.animate(amountOfRotations);
                break;
            case 'o':
                scene.setPreviousRotation();
                scene.animate(amountOfRotations);
                break;
            case 's':
                scene.displayRotationMatrix();
                break;
            case 't':
                scene.setTranslation();
                scene.animate();
                break;
            case 'd':
                scene.displayPoints();
                break;
            case 'c':
                scene.displayLenght();
                break;
            case 'm':
                displayMenu();
                break;
            case 'q':
                displayMenu();
                break;
        }
    } while (option != 'q');
}


void displayMenu() {
    std::cout << "\n r - rotate cuboid" << std::endl;
    std::cout << " o - repeat previous rotation" << std::endl;
    std::cout << " s - show rotation matrix" << std::endl;
    std::cout << " t - translate cuboid" << std::endl;
    std::cout << " d - display cuboid's points" << std::endl;
    std::cout << " c - check length of cuboid's sides" << std::endl;
    std::cout << " m - show menu" << std::endl;
    std::cout << " q - quit" << std::endl;
}


