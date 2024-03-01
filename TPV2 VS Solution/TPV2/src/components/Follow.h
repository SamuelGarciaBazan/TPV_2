#pragma once
#include "../ecs/Component.h"

class Transform;
class Vector2D;

class Follow :
    public ecs::Component
{
public:

    __CMPID_DECL__(ecs::cmp::FOLLOW)

    Follow(Vector2D* fighterPos);
    ~Follow();

    void update() override;

    void initComponent() override;

private:

    Vector2D* fighterPos;
    
    Transform* myTransform;
};

