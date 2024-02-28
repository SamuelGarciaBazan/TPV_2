#pragma once
#include "../ecs/Component.h"
#include <iostream>

class Texture;

class Health :
    public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::HEALTH);

    Health(std::string name);
    ~Health();

    void render() override;
private:

    Texture* healthTexture;
    int lifes = 0;
};

