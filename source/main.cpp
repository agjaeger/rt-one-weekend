
#include <iostream>

// Render
#include "Camera.h"
#include "Image.h"

// Test
#include "TestScenes.h"

using namespace rtow::math;
using namespace rtow::render;
using namespace rtow::scene;
using namespace rtow::test;

Vector3
getColor (
    Ray p_r,
    Intersectable *p_world,
    int p_depth=0
) {
    Intersection intersectionRecord;
    bool primaryRayHit = p_world->intersect(p_r, 0.001f, 100.0f, intersectionRecord);

    if (primaryRayHit) {
        Ray scatterRay;
        Vector3 attenuation;
        bool scatterRayHit = intersectionRecord.material->scatter(
            p_r, 
            intersectionRecord,
            attenuation,
            scatterRay
        );

        if (scatterRayHit && p_depth < 10) {
            return attenuation * getColor(scatterRay, p_world, p_depth+1);
        } else {
            return Vector3(0,0,0);
        }
    }

    Vector3 uv_direction = unitVector(p_r.direction());
    float t = 0.5f * (uv_direction.y() + 1);
    return (1.0f-t) * Vector3(1, 1, 1) + t * Vector3(0.5f, 0.7f, 1.0f);
}

int main() {
    std::string desc;
    Intersectable *world = bubble(desc);

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
                pixelColor = pixelColor + getColor(r, world);
            }

            pixelColor = pixelColor / float(numSamples);
            output.setPixel(x, y, pixelColor);
        }
    }
    
    output.write("render.png");
  
    free(world);
    return 0;
}