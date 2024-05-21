#pragma once

#include "../ecs/Component.h"

class Ghost :public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::GHOST);

    Ghost() {};
    ~Ghost() {};

    bool move = true;


};

