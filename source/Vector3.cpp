
#include "Vector3.h"

using namespace rtow::math;

Vector3::Vector3 () {
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
}

Vector3::Vector3 (
    float p_x,
    float p_y,
    float p_z
) {
    data[0] = p_x;
    data[1] = p_y;
    data[2] = p_z;
}

float
Vector3::x () {
    return data[0];
}

float
Vector3::y () {
    return data[1];
}

float
Vector3::z () {
    return data[2];
}

float
Vector3::r () {
    return data[0];
}

float
Vector3::g() {
    return data[1];
}

float
Vector3::b() {
    return data[2];
}

float&
Vector3::operator[] (
    int p_index
) {
    return data[p_index];
}

Vector3
Vector3::operator+ (
    Vector3& p_vec
) {
    return Vector3 (
        data[0] + p_vec.x(),
        data[1] + p_vec.y(),
        data[2] + p_vec.z()
    );
}

Vector3
Vector3::operator- (
    Vector3& p_vec
) {
    return Vector3 (
        data[0] - p_vec.x(),
        data[1] - p_vec.y(),
        data[2] - p_vec.z()
    );
}

Vector3
Vector3::operator/ (
    float p_value
) {
    return Vector3 (
        data[0] / p_value,
        data[1] / p_value,
        data[2] / p_value
    );
}

Vector3&
Vector3::operator+= (
    Vector3& p_vec
) {
    data[0] += p_vec.x();
    data[1] += p_vec.y();
    data[2] += p_vec.z();
    
    return *this;
}

Vector3&
Vector3::operator-= (
    Vector3& p_vec
) {
    data[0] -= p_vec.x();
    data[1] -= p_vec.y();
    data[2] -= p_vec.z();
    
    return *this;
}

Vector3&
Vector3::operator*= (
    Vector3& p_vec
) {
    data[0] *= p_vec.x();
    data[1] *= p_vec.y();
    data[2] *= p_vec.z();
    
    return *this;
}

Vector3&
Vector3::operator/= (
    Vector3& p_vec
) {
    data[0] /= p_vec.x();
    data[1] /= p_vec.y();
    data[2] /= p_vec.z();
    
    return *this;
}

Vector3&
Vector3::operator*= (
    float p_value
) {
    data[0] *= p_value;
    data[1] *= p_value;
    data[2] *= p_value;
    
    return *this;
}

Vector3&
Vector3::operator/= (
    float p_value
) {
    data[0] /= p_value;
    data[1] /= p_value;
    data[2] /= p_value;
    
    return *this;
}

// Namespace function implementations

float
rtow::math::length (
    Vector3 p_vec
) {
    return sqrt(rtow::math::squaredLength(p_vec));
}

float
rtow::math::squaredLength (
    Vector3 p_vec
) {
    return
          pow(p_vec.x(), 2) 
        + pow(p_vec.y(), 2) 
        + pow(p_vec.z(), 2);
}

Vector3
rtow::math::unitVector (
    Vector3 p_vec
) {
    return p_vec / rtow::math::length(p_vec);
}

float
rtow::math::dot (
    Vector3 &p_vec1,
    Vector3 &p_vec2
) {
    return
          p_vec1.x() * p_vec2.x()
        + p_vec1.y() * p_vec2.y()
        + p_vec1.z() * p_vec2.z();
}

Vector3
rtow::math::cross (
    Vector3 &p_vec1,
    Vector3 &p_vec2
) {
    return Vector3 (
        p_vec1.y() * p_vec2.z() - p_vec1.z() * p_vec2.y(),
        -(p_vec1.z() * p_vec2.x() - p_vec1.x() * p_vec2.z()),
        p_vec1.x() * p_vec2.y() - p_vec1.y() * p_vec2.x()
    );
}
