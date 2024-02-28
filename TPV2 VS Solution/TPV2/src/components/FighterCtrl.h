#pragma once
#include "../ecs/Component.h"


class Transform;

class FighterCtrl :
    public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::FIGHTERCTRL)

    FighterCtrl();
    ~FighterCtrl();

    void update() override;

    void initComponent() override;

private:

    Transform* myTransform;
    
    double thrust = 0.1;

    double rotationRate = 3.3;

    double speedLimit = 3.0;

};

