
#include "AABB.h"

using namespace rtow::scene;

AABB::AABB () {}

AABB::AABB (
    Vector3 p_min,
    Vector3 p_max
) {
    m_min = p_min;
    m_max = p_max;
}

Vector3
AABB::min () {
    return m_min;
}

Vector3
AABB::max () {
    return m_max;
}

bool
AABB::intersect (
    Ray p_r,
    float p_tMin,
    float p_tMax
) {
    int maxDim = 3;
    for (int dimId = 0; dimId < maxDim; dimId++) {
        float t0 = rtow::scene::min(
            (m_min[dimId] - p_r.origin()[dimId]) / p_r.direction()[dimId],
            (m_max[dimId] - p_r.origin()[dimId]) / p_r.direction()[dimId]
        );
        
        float t1 = rtow::scene::max(
            (m_min[dimId] - p_r.origin()[dimId]) / p_r.direction()[dimId],
            (m_max[dimId] - p_r.origin()[dimId]) / p_r.direction()[dimId]
        );
        
        p_tMin = rtow::scene::max(t0, p_tMin);
        p_tMax = rtow::scene::min(t1, p_tMax);
    
        if (p_tMax <= p_tMin) {
            return false;
        }
    }
    
    return true;
}

AABB 
rtow::scene::surroundingBox (
    AABB p_box1, 
    AABB p_box2
) {
    Vector3 small (
        rtow::scene::min(p_box1.min().x(), p_box2.min().x()),
        rtow::scene::min(p_box1.min().y(), p_box2.min().y()),
        rtow::scene::min(p_box1.min().z(), p_box2.min().z())
    );
    
    Vector3 big (
        rtow::scene::max(p_box1.max().x(), p_box2.max().x()),
        rtow::scene::max(p_box1.max().y(), p_box2.max().y()),
        rtow::scene::max(p_box1.max().z(), p_box2.max().z())
    );
    
    return AABB(small, big);
}