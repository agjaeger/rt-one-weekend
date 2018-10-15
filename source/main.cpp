
#include <iostream>
#include <memory>
#include <cstdlib>

#include "Camera.h"
#include "Vector3.h"
#include "Ray.h"
#include "Image.h"

#include "Sphere.h"
#include "IntersectableList.h"

using namespace rtow::render;
using namespace rtow::math;
using namespace rtow::scene;

Vector3
randomInUnitSphere () {
    Vector3 p;
    
    do {
        Vector3 v_rand = Vector3(
            rand()/float(RAND_MAX),
            rand()/float(RAND_MAX),
            rand()/float(RAND_MAX)
        );
        
        p = 2.0f * v_rand - Vector3(1,1,1);        
    } while (squaredLength(p) >= 1.0f);
    
    return p;
}

Vector3
intersectColor (
    Ray p_r,
    Intersectable* p_world
) {
    Intersection intersectionRecord;
    if (p_world->intersect(p_r, 0.01f, 100.0f, intersectionRecord)) {
        Vector3 target = intersectionRecord.normal + randomInUnitSphere();
        
        return 0.5f * intersectColor(Ray(intersectionRecord.point, target), p_world);
    } else {
        Vector3 uv_direction = unitVector(p_r.direction());
        float t = 0.5f * (uv_direction.y() + 1);
        
        //return Vector3(0,0,0);
        return (1.0f-t) * Vector3(1, 1, 1) + t * Vector3(0.5f, 0.7f, 1.0f);
    }
}

int main() {
    Intersectable *world = new IntersectableList({
        new Sphere(Vector3(0, 0, -1), 0.5f),
        new Sphere(Vector3(0, -100.5, -1), 100.0f)
    });

    uint numSamples = 100;
    Image output (200, 100);
    Camera camera;
    
    for (int y = 0; y < output.height(); ++y) {
        for (int x = 0; x < output.width(); ++x) {
            Vector3 pixelColor = Vector3(0,0,0);
            
            for (int sample = 0; sample < numSamples; sample++) {
                float ss_u = (x + (rand()/float(RAND_MAX))) / output.width();
                float ss_v = (y + (rand()/float(RAND_MAX))) / output.height();

                Ray r = camera.getRay(ss_u, ss_v);
                pixelColor = pixelColor + intersectColor(r, world);
            }
            
            pixelColor = pixelColor / float(numSamples);
            output.setPixel(x, y, pixelColor);
        }
    }
    
    output.write("render.png");
  
    free(world);
    return 0;
}