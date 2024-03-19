#pragma once
#include "../ecs/Component.h"

class Transform;
class Image;

class ShowAtOpposieSide :
    public ecs::Component
{

public:

    __CMPID_DECL__(ecs::cmp::SHOWATOPOSSITESIDE);

    ShowAtOpposieSide();
    ~ShowAtOpposieSide();

    void update() override;
    
    void initComponent() override;

private:
    Transform* myTransform;
    //Image* myImage;

};

