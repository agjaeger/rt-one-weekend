
#pragma once

#include <cstdlib>
#include "Vector3.h"

namespace rtow {
    namespace math {
        class Random {
            public:
                static Vector3 unitSphere() {
                    Vector3 p;
                    
                    do {
                        Vector3 v_rand = Vector3(
                            rand()/float(RAND_MAX),
                            rand()/float(RAND_MAX),
                            rand()/float(RAND_MAX)
                        );
                        
                        p = 2.0f * v_rand - Vector3(1,1,1);        
                    } while (squaredLength(p) >= 1.0f);
                    
                    return p;
                };
        };
    }
};