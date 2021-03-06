
#pragma once

#include <math.h>
#include <string>
#include <array>
#include <iostream>
#include <sstream>

namespace rtow {
    namespace math {
        class Vector3 {
            public:
                Vector3();
                Vector3(float x, float y, float z);

                float x();
                float y();
                float z();
                
                float r();
                float g();
                float b();

                std::string toString();
                float& operator[](int i);
                
            private:
                std::array<float, 3> data;
        };

        std::ostream& operator<<(std::ostream &os, Vector3 v);
        
        Vector3 operator+(Vector3 lhs, Vector3 rhs);
        Vector3 operator+(Vector3 lhs, float rhs);
        Vector3 operator-(Vector3 lhs, Vector3 rhs);
        Vector3 operator-(Vector3 lhs, float rhs);
        Vector3 operator/(Vector3 lhs, float rhs);
        Vector3 operator*(Vector3 lhs, Vector3 rhs);
        Vector3 operator*(Vector3 lhs, float rhs);
        Vector3 operator*(float lhs, Vector3 rhs);

        Vector3 reflect (Vector3 v1, Vector3 v2);
        bool refract (Vector3 v, Vector3 n, float ni_over_nt, Vector3 &refracted);
        
        float length(Vector3 v);
        float squaredLength(Vector3 v);

        Vector3 unitVector(Vector3 v);
        float dot(Vector3 v1, Vector3 v2);
        Vector3 cross(Vector3 v1, Vector3 v2);
    };
};