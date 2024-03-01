#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform;


class TowardDestination :
    public ecs::Component
{
public: 
    __CMPID_DECL__(ecs::cmp::TOWARDSDESTINATION);

    TowardDestination();
    ~TowardDestination();

    void update() override;
    void initComponent() override;


private:

    Transform* myTransform;
    Vector2D destPos;

    Vector2D newDest();

    Vector2D newVelVector();
};

