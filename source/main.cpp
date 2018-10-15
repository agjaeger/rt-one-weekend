
#include <iostream>

#include "Vector3.h"
#include "Ray.h"
#include "Image.h"

using namespace rtow::render;
using namespace rtow::math;

bool
intersectSphere (
    Vector3 p_sphereOrigin, 
    float p_radius, 
    Ray p_r
) {
    // Move ray to sphere origin
    Vector3 ws_newRayOrigin = p_r.origin() - p_sphereOrigin;
    
    // Calculate discriminant
    float a = dot(p_r.direction(), p_r.direction());
    float b = 2 * dot(ws_newRayOrigin, p_r.direction());
    float c = dot(ws_newRayOrigin, ws_newRayOrigin) - pow(p_radius, 2);
    float discriminant = pow(b,2) - 4*a*c;
    
    // if discriminant is 0; we missed
    // else we hit
    return (discriminant > 0);
}

Vector3
intersectColor (
    Ray p_r
) {
    if (intersectSphere(Vector3(0, 0, -1), 0.5, p_r)) {
        return Vector3(1, 0, 0);
    }
    
    float t = 0.5f * (unitVector(p_r.direction()).y() + 1);
    return (1 - t) * Vector3(1, 1, 1) + t * Vector3(0.5f, 0.7f, 1.0f);
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
