
#pragma once

#include "Vector3.h"
#include "Intersectable.h"

namespace rtow {
    namespace scene {
        class Sphere : public Intersectable {
            public:
                Sphere(Vector3 origin, float radius);

                Vector3 normal(Vector3 point);
                bool intersect(Ray r, float tMin, float tMax, Intersection &intersection);                
            private:
                Vector3 m_origin;
                float m_radius;
        };
    }

};