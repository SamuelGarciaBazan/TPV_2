#pragma once
#include "../ecs/Component.h"


class Transform;

class DeAcceleration :
    public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::DEACCELERATION);

    DeAcceleration();
    ~DeAcceleration();

    void update() override;

    void initComponent() override;

private:

    Transform* myTransform;

    double deAcelerationRate = 0.99;
    double minVel = 0.05;
};

