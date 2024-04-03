#pragma once
#include "../ecs/System.h"

#include <utility>

class Transform;

class CollisionsSystem
	:public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::COLLISIONS);

    CollisionsSystem();

    ~CollisionsSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:

    void checkCollisions();

    std::pair<bool,ecs::entity_t> collisionsGhosts();

    std::pair<bool, ecs::entity_t> collisionsFood();

    bool collidesWithRotation(Transform* t1, Transform* t2);
};

