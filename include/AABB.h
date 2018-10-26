
#pragma once

#include "Vector3.h"
#include "Ray.h"

using namespace rtow::math;

namespace rtow {
    namespace scene {
        inline float min (float a, float b) {
            return a < b ? a : b;
        } 
        
        inline float max (float a, float b) {
            return a > b ? a : b;
        }
        
        class AABB {
            public:
                AABB ();
                AABB (Vector3 min, Vector3 max);
                
                Vector3 min ();
                Vector3 max ();
                
                bool intersect (Ray r, float tMin, float tMax);
                
            private:
                Vector3 m_min;
                Vector3 m_max;
        };
        
        AABB surroundingBox (AABB box1, AABB box2);
    };
};