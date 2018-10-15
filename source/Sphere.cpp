
#include "Sphere.h"

using namespace rtow::scene;

Sphere::Sphere (
    Vector3 p_origin, 
    float p_radius
) {
    m_origin = p_origin;
    m_radius = p_radius;
}

bool
Sphere::intersect (
    Ray p_ray,
    float p_tmin,
    float p_tmax,
    Intersection &p_intersection
) {
    Vector3 oc = p_ray.origin() - m_origin;
    
    float a = dot(p_ray.direction(), p_ray.direction());
    float b = dot(oc, p_ray.direction());
    float c = dot(oc, oc) - pow(m_radius, 2);

    float discriminant = pow(b, 2) - a*c;
    
    if (discriminant <= 0) {
        return false;
    } else {
        float root = (-b - sqrt(pow(b,2) - a*c)) / a;
        if (root > p_tmin && root < p_tmax) {
            p_intersection.distance = root;
            p_intersection.point = p_ray.at(root);
            p_intersection.normal = normal(p_ray.at(root));
            
            return true;
        }
        
        root = (-b + sqrt(pow(b,2) - a*c)) / a;
        if (root > p_tmin && root < p_tmax) {
            p_intersection.distance = root;
            p_intersection.point = p_ray.at(root);
            p_intersection.normal = normal(p_ray.at(root));
            
            return true;
        }
    }    
}

Vector3
Sphere::normal (
    Vector3 p_point
) {
    return (p_point - m_origin) / m_radius;
}