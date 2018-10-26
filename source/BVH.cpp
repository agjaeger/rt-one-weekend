
#include "BVH.h"

#include <iostream>

using namespace rtow::scene;

int
boxXCompare (const void * a, const void * b) {
    AABB boxLeft, boxRight;
    Intersectable *ah = *(Intersectable**)a;
    Intersectable *bh = *(Intersectable**)b;
    
    if (
        !ah->boundingBox(boxLeft)
     || !bh->boundingBox(boxRight)
    ) {
        // error
        std::cout << "Box X compare Error" << std::endl;
    } 
    
    if (boxLeft.min().x() - boxRight.min().x() < 0.0f) {
        return -1;
    } else {
        return 1;
    }
}

int
boxYCompare (const void * a, const void * b) {
    AABB boxLeft, boxRight;
    Intersectable *ah = *(Intersectable**)a;
    Intersectable *bh = *(Intersectable**)b;
    
    if (
        !ah->boundingBox(boxLeft)
     || !bh->boundingBox(boxRight)
    ) {
        // error
        std::cout << "Box Y compare Error" << std::endl;
    } 
    
    if (boxLeft.min().y() - boxRight.min().y() < 0.0f) {
        return -1;
    } else {
        return 1;
    }
}

int
boxZCompare (const void * a, const void * b) {
    AABB boxLeft, boxRight;
    Intersectable *ah = *(Intersectable**)a;
    Intersectable *bh = *(Intersectable**)b;
    
    if (
        !ah->boundingBox(boxLeft)
     || !bh->boundingBox(boxRight)
    ) {
        // error
        std::cout << "Box Z compare Error" << std::endl;
    } 
    
    if (boxLeft.min().z() - boxRight.min().z() < 0.0f) {
        return -1;
    } else {
        return 1;
    }
}

BVHNode::BVHNode() {}

BVHNode::BVHNode (
    std::vector<Intersectable*> p_objs
) {
    int axis = int(3 * Random::getFloat());
    
    if (axis == 0) {
        Intersectable **objData = p_objs.data();
        
        qsort(objData, (int)p_objs.size(), sizeof(Intersectable*), boxXCompare);
        
        p_objs = std::vector<Intersectable*>(objData, objData + p_objs.size());
    }
    
    else if (axis == 1) {
        Intersectable **objData = p_objs.data();
        
        qsort(p_objs.data(), (int)p_objs.size(), sizeof(Intersectable*), boxYCompare);
        
        p_objs = std::vector<Intersectable*>(objData, objData + p_objs.size());
    }
    
    else {
        Intersectable **objData = p_objs.data();
        
        qsort(p_objs.data(), (int)p_objs.size(), sizeof(Intersectable*), boxZCompare);
        
        p_objs = std::vector<Intersectable*>(objData, objData + p_objs.size());
    }
    
    if (p_objs.size() == 1) {
        m_left = m_right = p_objs[0];
    } 
    
    else if (p_objs.size() == 2) { 
        m_left = p_objs[0];
        m_right = p_objs[1];
    }
    
    else {
        std::size_t halfSize = p_objs.size() / 2;
        
        std::vector<Intersectable*> lowHalf (p_objs.begin(), p_objs.begin() + halfSize);
        std::vector<Intersectable*> highHalf (p_objs.begin() + halfSize, p_objs.end());
        
        m_left = new BVHNode(lowHalf);
        m_right = new BVHNode(highHalf);
    }
    
    
    AABB boxLeft, boxRight;
    
    if (
        !m_left->boundingBox(boxLeft) 
     || !m_right->boundingBox(boxRight) 
    ) {
        std::cout << "BB Error" << std::endl;
    }
    
    m_bbox = surroundingBox(boxLeft, boxRight);
}

bool
BVHNode::intersect (
    Ray p_ray,
    float p_tMin,
    float p_tMax,
    Intersection &p_record
) {
    if (m_bbox.intersect(p_ray, p_tMin, p_tMax)) {
        Intersection leftRec, rightRec;
        
        bool hitLeft = m_left->intersect(p_ray, p_tMin, p_tMax, leftRec);
        bool hitRight = m_right->intersect(p_ray, p_tMin, p_tMax, rightRec);
        
        if (hitLeft && hitRight) {
            if (leftRec.distance < rightRec.distance) {
                p_record = leftRec;
            } else {
                p_record = rightRec;
            }
            //std::cout << "intersect is true" << std::endl;

            return true;
        }
        
        else if (hitLeft) {
            p_record = leftRec;
            //std::cout << "intersect is true" << std::endl;

            return true;
        }
        
        else if (hitRight) {
            p_record = rightRec;
            //std::cout << "intersect is true" << std::endl;

            return true;
        }
    }

    //std::cout << "intersect is false" << std::endl;
    return false;
}

bool
BVHNode::boundingBox (
    AABB &p_bbox
) {
    p_bbox = m_bbox;
    return true;
};