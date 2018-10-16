
#pragma once

#include "Material.h"
#include "Texture.h"
#include "Random.h"
#include "Vector3.h"

using namespace rtow::math;
using namespace rtow::scene;

namespace rtow {
    namespace render {
        class Lambertian : public Material {
            public:
                Lambertian (Texture *albedo);
                ~Lambertian ();

                virtual bool scatter (Ray in, Intersection record, Vector3 &attentuation, Ray &out);

            private:
                Texture *m_albedo;
        };
    };
};