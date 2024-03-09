#pragma once
#include "../ecs/Component.h"

class Transform;

class ConstRotation :
    public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::CONSTROTATION);

    ConstRotation();
    ConstRotation(float angle);
    ~ConstRotation();

    void initComponent() override;
    void update() override;

private:
    float angle;
    Transform* myTransform;
};

