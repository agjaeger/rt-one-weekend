
#include "IntersectableList.h"

using namespace rtow::scene;

IntersectableList::IntersectableList() {}

IntersectableList::IntersectableList (
    std::initializer_list<Intersectable*> p_objs
) : m_objs (p_objs) {}

void 
IntersectableList::append (
    Intersectable *p_obj
) {
    m_objs.push_back(p_obj);
}

bool
IntersectableList::intersect (
    Ray p_ray,
    float p_tmin,
    float p_tmax,
    Intersection &p_record
) {
    bool intersectedAny = false;
    float closest = p_tmax;

    Intersection tempRecord;
    for (Intersectable* obj : m_objs) {
        if (obj->intersect(p_ray, p_tmin, p_tmax, tempRecord)) {
            intersectedAny = true;

            if (tempRecord.distance < closest) {
                closest = tempRecord.distance;
                p_record = tempRecord;
            }
        }
    }
    
    return intersectedAny;
}