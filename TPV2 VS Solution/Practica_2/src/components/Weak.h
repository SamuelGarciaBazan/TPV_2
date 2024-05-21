#pragma once

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"


class Weak 
    : public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::WEAK);


    Weak(int nCol, Vector2D initialPos);
    ~Weak();


    int nCol;

    Vector2D initialPos;

};

