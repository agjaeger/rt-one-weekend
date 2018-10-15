
#include <iostream>

#include "Vector3.h"
#include "Ray.h"
#include "Image.h"
#include "Sphere.h"

using namespace rtow::render;
using namespace rtow::math;
using namespace rtow::scene;

Sphere s (Vector3(0, 0, -1), 0.5);

Vector3
intersectColor (
    Ray p_r
) {
    Intersection sphereIntersection;
    bool didIntersect = s.intersect(p_r, 0.01, 10, sphereIntersection);
    
    // if the sphere was hit
    if (didIntersect) {
        Vector3 uv_normal = unitVector(sphereIntersection.normal);

        return 0.5 * Vector3(
            uv_normal.x() + 1,
            uv_normal.y() + 1, 
            uv_normal.z() + 1
        );            
    } else {
        Vector3 uv_direction = unitVector(p_r.direction());
        float t = 0.5f * (uv_direction.y() + 1);
        
        return (1-t) * Vector3(1, 1, 1) + t * Vector3(0.5f, 0.7f, 1.0f);
    }
}

int main() {
    Image output (200, 100);

    Vector3 ws_lowerLeftCorner (-2, -1, -1);
    Vector3 ss_horizontal (4, 0, 0);
    Vector3 ss_vertical (0, 2, 0);
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

    return 0;
}
