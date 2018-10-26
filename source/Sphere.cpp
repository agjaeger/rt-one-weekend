
#include "Sphere.h"

using namespace rtow::scene;

Sphere::Sphere (
    Vector3 p_origin, 
    float p_radius,
    Material *p_material
) {
    m_origin = p_origin;
    m_radius = p_radius;
    m_material = p_material;
}

Sphere::~Sphere () {
    free(m_material);
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
    
    if (discriminant > 0) {
        float root = (-b - sqrt(pow(b,2) - a*c)) / a;
        if (root > p_tmin && root < p_tmax) {
            fillIntersection(root, p_ray, p_intersection);
            return true;
        }
        
        root = (-b + sqrt(pow(b,2) - a*c)) / a;
        if (root > p_tmin && root < p_tmax) {
            fillIntersection(root, p_ray, p_intersection);
            return true;
        }
    }
    
    return false;
}

bool
Sphere::boundingBox (
    AABB& p_box
) {
    p_box = AABB(
        m_origin - Vector3(m_radius, m_radius, m_radius),
        m_origin + Vector3(m_radius, m_radius, m_radius)
    );
    
    return true;
}

void
Sphere::fillIntersection (
    float p_dist,
    Ray p_ray,
    Intersection &p_intersection
) {
    p_intersection.distance = p_dist;
    p_intersection.point = p_ray.at(p_dist);
    p_intersection.normal = (p_ray.at(p_dist) - m_origin) / m_radius;
    p_intersection.material = m_material;
}