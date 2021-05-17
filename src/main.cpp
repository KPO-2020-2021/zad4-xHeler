#include "Polygon.h"

int main() {

    Polygon<3> triangle(30, "#FF0000");
    Polygon rectangle(30, "#DAA520");
    Polygon<6> hexagon(30, "#006400");
    Polygon<360> circle(30, "#87CEEB");

    triangle.translation(80, 0, 0);
    hexagon.translation(-80, 0, 0);
    circle.translation(0, 50, 0);

    triangle.draw();
    rectangle.draw();
    hexagon.draw();
    circle.draw();

    plt.initializePlot3D();

}

