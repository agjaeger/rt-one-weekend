
#pragma once

#include <string>

// Math
#include "Vector3.h"
#include "Ray.h"

// Render
#include "Camera.h"
#include "Image.h"

#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

#include "Texture.h"
#include "ConstantTexture.h"
#include "CheckerTexture.h"

// Scene
#include "Sphere.h"
#include "IntersectableList.h"

using namespace rtow::math;
using namespace rtow::render;
using namespace rtow::scene;

namespace rtow {
    namespace test {
        Intersectable* bubble (std::string& p_desc) {
            p_desc = "Three Spheres: Bubble, Diffuse, Metal";
            
            return new IntersectableList({
                new Sphere(Vector3(0, 0, -1), 0.5f, new Lambertian(
                    new ConstantTexture(Vector3(0.8, 0.3, 0.3))
                )),
               
                new Sphere(Vector3(0, -100.5, -1), 100.0f, new Lambertian(
                    new CheckerTexture(
                        new ConstantTexture(Vector3(0.8, 0.8, 0.8)),
                        new ConstantTexture(Vector3(0.8, 0.8, 0.0))
                    )
                )),

                new Sphere(Vector3(1, 0, -1), 0.5f, new Metal(
                        new ConstantTexture(Vector3(0.8, 0.6, 0.2))
                    )
                ),
            
                new Sphere(Vector3(-1, 0, -1), 0.5f, new Dielectric(1.5)),
                new Sphere(Vector3(-1, 0, -1), -0.45f, new Dielectric(1.5))
            });
        };
    };
};