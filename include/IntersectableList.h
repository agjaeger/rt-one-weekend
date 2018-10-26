
#pragma once

#include <memory>
#include <vector>
#include <initializer_list>

#include "Intersectable.h"

namespace rtow {
    namespace scene {
        class IntersectableList : public Intersectable {
            public:
                IntersectableList();
                IntersectableList(std::initializer_list<Intersectable*> objs);
                
                void append(Intersectable* object);
                virtual bool intersect(Ray r, float t_min, float t_max, Intersection &intersection);
                virtual bool boundingBox(AABB& box);
                
            private:
                std::vector<Intersectable*> m_objs;
        };
    };
};