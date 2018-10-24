
#include <iostream>

#include "zupply.h"

#include "Random.h"

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
    Intersectable *world = randomSpheres(desc);
    
    std::cout << "Scene: " << desc << std::endl;
     
    uint numSamples = 2;
    Image output (2, 1);
    
    Camera camera (
        Vector3(3,1,2),
        Vector3(0,0,-1),
        Vector3(0,1,0),
        60,
        float(output.width()) / float(output.height())
    );
    
    for (int y = 0; y < output.height(); ++y) {
        for (int x = 0; x < output.width(); ++x) {
            Vector3 pixelColor = Vector3(0, 0, 0);
            
            for (int sample = 0; sample < numSamples; sample++) {
                float ss_u = (x + Random::getFloat()) / output.width();
                float ss_v = (y + Random::getFloat()) / output.height();

                Ray cameraRay = camera.getRay(ss_u, ss_v);
                pixelColor = pixelColor + getColor(cameraRay, world);
            }

            pixelColor = pixelColor / float(numSamples);
            output.setPixel(x, y, pixelColor);
        }
    }

    output.write("render.png");

    free(world);
    return 0;
}