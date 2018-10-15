
#include <iostream>

#include "Vector3.h"
#include "Image.h"

using namespace rtow::render;
using namespace rtow::math;

int main() {
    Image output (640, 480);

    for (int y = 0; y < output.height(); ++y) {
        for (int x = 0; x < output.width(); ++x) {
            Vector3 pixelColor (
                x / float(output.width()), 
                y / float(output.height()), 
                0.2f
            );

            output.setPixel(x, y, pixelColor);
        }
    }
    
    output.write("render.png");
    
    Vector3 one = Vector3(1, 0, 0);
    Vector3 two = Vector3(2, 0, 0);
    Vector3 z = Vector3(0, 0, 1);
    Vector3 three = one + two;
    
    std::cout << three.x() << " " << three.y() << " " << three.z() << std::endl; 
    std::cout << unitVector(two).x() << " " << unitVector(two).y() << " " << unitVector(two).z() << std::endl; 
    std::cout << cross(one, z).x() << " " << cross(one, z).y() << " " << cross(one, z).z() << std::endl; 
    

    return 0;
}
