
#pragma once

#include "Material.h"
#include "Texture.h"

namespace rtow {
    namespace render {
        class DiffuseLight : public Material {
            public:
                DiffuseLight(Texture *emissive);
                ~DiffuseLight();
                
                virtual bool scatter (Ray r_in, Intersection record, Vector3 &attenuation, Ray &scattered);
                virtual Vector3 emitted (float ss_u, float ss_v, Vector3 ws_xyz);
                
            private:
                Texture *m_emissive;
        };
    };
};