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

    void updateMiracleFruits();


};

