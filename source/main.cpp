
#include <iostream>

#include "Vector3.h"
#include "Ray.h"
#include "Image.h"

using namespace rtow::render;
using namespace rtow::math;

Vector3
intersectColor (
    Ray& r
) {
    float t = 0.5f * (unitVector(r.direction()).y() + 1);
    return (1 - t) * Vector3(1, 0, 0) + t * Vector3(0, 1, 0);
}

int main() {
    Image output (200, 100);

    Vector3 ws_lowerLeftCorner (-2, -1, -1);
    Vector3 ss_horizontal (4, 0, 0);
    Vector3 ss_vertical (4, 0, 0);
    Vector3 ws_origin (0, 0, 0);

    for (int y = 0; y < output.height(); ++y) {
        for (int x = 0; x < output.width(); ++x) {
            float ss_u = float(x) / output.width();
            float ss_v = float(y) / output.height();
        
            Ray r (ws_origin, ws_lowerLeftCorner + ss_u*ss_horizontal + ss_v*ss_vertical);
            Vector3 c = intersectColor(r);
            
            output.setPixel(x, y, c);
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
