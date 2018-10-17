
#pragma once

#include "Ray.h"
#include "Intersectable.h"
#include "Vector3.h"

using namespace rtow::math;
using namespace rtow::scene;

namespace rtow {
    namespace render {
        class Material {
            public:
                virtual bool scatter (Ray r_in, Intersection record, Vector3 &attenuation, Ray &scattered) = 0;
                
                virtual Vector3 emitted (float ss_u, float ss_v, Vector3 ws_xyz) { 
                    return Vector3(0,0,0);
                }
        };
    };
};