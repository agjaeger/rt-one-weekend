
#pragma once

#include <cstdlib>
#include "Vector3.h"

namespace rtow {
    namespace math {
        class Random {
            public:
                static float getFloat() {
                    return rand() / float(RAND_MAX);
                }
                
                static Vector3 unitDisk() {
                    Vector3 p;
                    
                    do {
                        p = 2.0 * Vector3(Random::getFloat(), Random::getFloat(), 0.0f) - Vector3(1, 1, 0);
                    } while (dot(p,p) >= 1.0);
                    
                    return p;
                }
            
                static Vector3 unitSphere() {
                    Vector3 p;
                    
                    do {
                        Vector3 v_rand = Vector3(
                            Random::getFloat(),
                            Random::getFloat(),
                            Random::getFloat()
                        );
                        
                        p = 2.0f * v_rand - Vector3(1,1,1);        
                    } while (squaredLength(p) >= 1.0f);
                    
                    return p;
                };
        };
    }
};