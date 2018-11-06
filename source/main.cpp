
#include <iostream>
#include <chrono>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

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
    int p_depth=0,
    int p_maxDepth=10
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

        if (scatterRayHit && p_depth < p_maxDepth) {
            return attenuation * getColor(scatterRay, p_world, p_depth+1, p_maxDepth);
        } else {
            return Vector3(0,0,0);
        }
    }
    
    Vector3 uv_direction = unitVector(p_r.direction());
    float t = 0.5f * (uv_direction.y() + 1);
    return (1.0f-t) * Vector3(1, 1, 1) + t * Vector3(0.5f, 0.7f, 1.0f);
}

int main() {
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_every(std::chrono::seconds(10));
    auto infoLogger = spdlog::basic_logger_mt("rt-info", "output.log", true);
    auto perfLogger = spdlog::basic_logger_mt("rt-perf", "perf.log", true);
    
    std::string desc;
    Intersectable *world = randomSpheres(desc);    
    
    int outputWidth = 200;
    int outputHeight = 200;
    int numSamples = 20;
    int maxRecursionDepth = 10;
    
    Vector3 cameraFrom (13, 2, 3);
    Vector3 cameraTo (0,0,0);
    int fov = 20;
    float aperature = 0.0;
    float focusPlane = 2;
    
    Image output (outputWidth, outputHeight);    

    infoLogger->info("Scene: {}", desc);
    infoLogger->trace("Image Size {} x {}", outputWidth, outputHeight);
    infoLogger->trace("Number of Samples {}", numSamples);
    infoLogger->trace("Max Recursion Depth {}", maxRecursionDepth);
    infoLogger->trace("Camera Position {}", cameraFrom.toString());
    infoLogger->trace("Camera Looking at {}", cameraTo.toString());
    infoLogger->trace("Camera FOV {}", fov);

    perfLogger->info("Image Size {} x {}", outputWidth, outputHeight);
    perfLogger->info("Number of Samples {}", numSamples);
    perfLogger->info("Max Recursion Depth {}", maxRecursionDepth);
    
    Camera camera (
        cameraFrom,
        cameraTo,
        Vector3(0,1,0),
        fov,
        float(output.width()) / float(output.height()),
        aperature,
        focusPlane
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
        
        // write output after every scanline
        output.write("render.png");
    }

    output.write("render.png");

    free(world);
    return 0;
}