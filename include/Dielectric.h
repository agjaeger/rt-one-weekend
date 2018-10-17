
#pragma once

#include "Material.h"

namespace rtow {
    namespace render {
        class Dielectric : public Material {
            public:
                Dielectric (float ri);
                virtual bool scatter (Ray r_in, Intersection record, Vector3 &attenuation, Ray &scattered);
            
            private:
                float m_refIdx;
                
                float schlick (float p_cosine, float refIdx);
        };
    };
};