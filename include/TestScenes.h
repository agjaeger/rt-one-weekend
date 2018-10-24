
#pragma once

#include <string>

// Math
#include "Vector3.h"
#include "Ray.h"
#include "Random.h"

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
        
        Intersectable* oneSphere (std::string& p_desc) {
            p_desc = "One Sphere";
            
            return new IntersectableList({
                new Sphere(Vector3(0, 0, 0), 1, new Lambertian(
                    new ConstantTexture(Vector3(0.8, 0.3, 0.3))
                ))
            });
        };
        
        Intersectable* randomSpheres (std::string& p_desc) {
            p_desc = "A bunch of random spheres (cover image of book 1)";
            
            int n = 500;
            IntersectableList *sceneList = new IntersectableList();
            
            // floor sphere
            sceneList->append(new Sphere(
                Vector3(0, -1000, 0),
                1000,
                new Lambertian(
                    new ConstantTexture(Vector3(0.5, 0.5, 0.5))
                )
            ));
            
            // generate grid of small spheres
            for (int x = -11; x < 11; x++) {
                for (int z = -11; z < 11; z++) {
                    float materialChoice = Random::getFloat();
                    Vector3 sphereCenter = Vector3(
                        x + 0.9f * Random::getFloat(),
                        0.2f,
                        z + 0.9f * Random::getFloat()
                    );
                    
                    Material *sphereMat;
                    if (materialChoice < 0.8f) {
                        sphereMat = new Lambertian(new ConstantTexture(Vector3(
                            Random::getFloat() * Random::getFloat(), 
                            Random::getFloat() * Random::getFloat(), 
                            Random::getFloat() * Random::getFloat()
                        )));
                    } else if (materialChoice < 0.95f) {
                        sphereMat = new Metal(new ConstantTexture(Vector3(
                            0.5f * (1 + Random::getFloat()), 
                            0.5f * (1 + Random::getFloat()), 
                            0.5f * (1 + Random::getFloat())
                        )));
                    } else {
                        sphereMat = new Dielectric(1.5f);
                    }
                    
                    sceneList->append(new Sphere(sphereCenter, 0.2f, sphereMat));
                }
            }
            
            sceneList->append(new Sphere(Vector3(0, 1, 0), 1, new Dielectric(1.5f)));
            sceneList->append(new Sphere(Vector3(1.8, 1, -1), 1, new Metal(new ConstantTexture(Vector3(0.4, 0.2, 0.1f)))));
            sceneList->append(new Sphere(Vector3(-4, 1, 0), 1, new Lambertian(new ConstantTexture(Vector3(0.7, 0.6, 0.5f)))));
            
            return sceneList;
        };
    };
};