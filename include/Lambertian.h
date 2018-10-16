
#pragma once

#include "Material.h"
#include "Random.h"
#include "Vector3.h"

using namespace rtow::math;
using namespace rtow::scene;

namespace rtow {
    namespace render {
        class Lambertian : public Material {
            public:
                Lambertian (Vector3 albedo);
                virtual bool scatter (Ray in, Intersection record, Vector3 &attentuation, Ray &out);

            private:
                Vector3 m_albedo;
        };
    };
};