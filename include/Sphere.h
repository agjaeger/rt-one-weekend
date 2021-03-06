
#pragma once

#include "Intersectable.h"

using namespace rtow::math;

namespace rtow {
    namespace scene {
        class Sphere : public Intersectable {
            public:
                Sphere (Vector3 origin, float radius, Material *mat);
                ~Sphere ();

                virtual bool intersect (Ray r, float t_min, float t_max, Intersection &intersection);     
                virtual bool boundingBox (AABB &bbox);

            private:
                Vector3 m_origin;
                float m_radius;
                Material *m_material;

                void fillIntersection (float t, Ray r, Intersection& intersection);
        };
    };
};