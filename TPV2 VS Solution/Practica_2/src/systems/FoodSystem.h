#pragma once
#include "../ecs/System.h"

class FoodSystem
    :public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::FOOD);

    FoodSystem();

    ~FoodSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:
    
    void generateFruits();

    void resetTimers();

    void updateMiracleFruits();

    void destroyFruits();

    int fils = 6;
    int cols = 6;

    int spriteDefault = 12;
    int spriteMiracle = 15;

    
};

