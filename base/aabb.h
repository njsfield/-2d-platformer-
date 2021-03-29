//
//  aabb.h
//  ecs
//
//  Created by Nicholas Field on 28/03/2021.
//

#ifndef aabb_h
#define aabb_h

#include <iostream>
#include <SDL2/SDL.h>

struct AABB
{
    struct Pos
    {
        int x, y;
    };
    Pos min;
    Pos max;
    AABB(int xMin, int yMin, int xMax, int yMax):
        min(Pos{xMin, yMin}),
        max(Pos{xMax, yMax}) {};
};

inline std::ostream& operator<< (std::ostream &out, const AABB &aabb)
{
    out << "x: " << aabb.min.x << ", y: " << aabb.min.y << ", w: " << aabb.max.x << ", h: " << aabb.max.y;
    return out;
}

bool collide(AABB* a, AABB* b)
{
    float d1x = b->min.x - a->max.x;
    float d1y = b->min.y - a->max.y;
    float d2x = a->min.x - b->max.x;
    float d2y = a->min.y - b->max.y;

    if (d1x > 0.0f || d1y > 0.0f)
        return false;

    if (d2x > 0.0f || d2y > 0.0f)
        return false;
    
    return true;
};

#endif /* aabb_h */
