#pragma once
#include "../ecs/System.h"


class CollisionsSystem
	:public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::FOOD);

    CollisionsSystem();

    ~CollisionsSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:

    void checkCollisions();

};

