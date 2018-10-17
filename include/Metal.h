
#pragma once

#include "Texture.h"
#include "Material.h"

namespace rtow {
    namespace render {
        class Metal : public Material {
            public:
                Metal (Texture *albedo);
                ~Metal ();

                virtual bool scatter (Ray in, Intersection record, Vector3 &attentuation, Ray &out);

            private:
                Texture *m_albedo;

                Vector3 reflect (Vector3 v1, Vector3 v2);
        };
    };
};