#pragma once
#include "../ecs/Component.h"

class Vector2D;
class Transform;

class LookAt :
    public ecs::Component
{
public:

    __CMPID_DECL__(ecs::cmp::LOOKAT);

    LookAt(Vector2D* target);
    ~LookAt();

    void initComponent() override;
    void update() override;


private:

    Vector2D* target;
    Transform* myTransform;
};

