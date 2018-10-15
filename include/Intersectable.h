
#pragma once

#include "Vector3.h"
#include "Ray.h"

namespace rtow {
    namespace scene {
        struct Intersection {
            float distance;
            Vector3 point;
            Vector3 normal;
        };
        
        class Intersectable {
            public:
                virtual bool intersect(Ray r, float t_min, float t_max, Intersection &intersection) = 0;
        };
    };
};