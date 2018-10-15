
#include <iostream>
#include <memory>

#include "Vector3.h"
#include "Ray.h"
#include "Image.h"

#include "Sphere.h"
#include "IntersectableList.h"

using namespace rtow::render;
using namespace rtow::math;
using namespace rtow::scene;

Vector3
intersectColor (
    Ray p_r,
    Intersectable* p_world
) {
    Intersection intersectionRecord;
    if (p_world->intersect(p_r, 0.0f, 1000.0f, intersectionRecord)) {
        return 0.5f * Vector3(
            intersectionRecord.point.x() + 1,
            intersectionRecord.point.y() + 1,
            intersectionRecord.point.z() + 1
        );
    } else {
        Vector3 uv_direction = unitVector(p_r.direction());
        float t = 0.5f * (uv_direction.y() + 1);
        return (1.0f-t) * Vector3(1, 1, 1) + t * Vector3(0.5f, 0.7f, 1.0f);
    }
}

int main() {
    Intersectable *world = new IntersectableList({
        //new Sphere(Vector3(0, 0, -1), 0.5f),
        new Sphere(Vector3(0, -100.5f, -1), 100)
    });
    
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
            Vector3 c = intersectColor(r, world);
            
            output.setPixel(x, y, c);
        }
    }
    
    output.write("render.png");
  
    free(world);
    return 0;
}