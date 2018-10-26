
#pragma once

#include <memory>
#include <vector>

#include "Intersectable.h"
#include "Random.h"

namespace rtow {
    namespace scene {
        class BVHNode : public Intersectable {
            public:
                BVHNode ();
                BVHNode (std::vector<Intersectable*> objs);
                
                virtual bool intersect (Ray r, float tMin, float tMax, Intersection &record);
                virtual bool boundingBox (AABB& box);
                
            private:
                Intersectable *m_left;
                Intersectable *m_right;
                AABB m_bbox;
        };
    };
};