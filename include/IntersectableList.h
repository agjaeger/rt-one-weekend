
#pragma once

#include <memory>
#include <vector>
#include <initializer_list>

#include "Intersectable.h"

namespace rtow {
    namespace scene {
        class IntersectableList : public Intersectable {
            public:
                IntersectableList(std::initializer_list<Intersectable*> objs);
                virtual bool intersect(Ray r, float t_min, float t_max, Intersection &intersection);

            private:
                std::vector<Intersectable*> m_objs;
        };
    };
};