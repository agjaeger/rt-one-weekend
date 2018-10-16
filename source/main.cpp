
#include <iostream>
#include <memory>
#include <cstdlib>

#include "Camera.h"
#include "Vector3.h"
#include "Ray.h"
#include "Image.h"

#include "Sphere.h"
#include "IntersectableList.h"

#include "Material.h"
#include "Lambertian.h"

#include "Texture.h"
#include "ConstantTexture.h"
#include "CheckerTexture.h"

using namespace rtow::render;
using namespace rtow::math;
using namespace rtow::scene;

Vector3
getColor (
    Ray p_r,
    Intersectable *p_world,
    int p_depth=0
) {
    Intersection intersectionRecord;
    bool primaryRayHit = p_world->intersect(p_r, 0.01f, 100.0f, intersectionRecord);

    if (primaryRayHit) {
        Ray scatterRay;
        Vector3 attenuation;

        // segfaults without if???
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

    else {
        Vector3 uv_direction = unitVector(p_r.direction());
        float t = 0.5f * (uv_direction.y() + 1);
        return (1.0f-t) * Vector3(1, 1, 1) + t * Vector3(0.5f, 0.7f, 1.0f);
    }
}

int main() {
    Intersectable *world = new IntersectableList({
        new Sphere(Vector3(0, 0, -1), 0.5f, new Lambertian(new ConstantTexture(Vector3(0.8, 0.3, 0.3)))),
        new Sphere(Vector3(0, -100.5, -1), 100.0f, new Lambertian(new ConstantTexture(Vector3(0.1, 0.3, 0.3))))
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