#pragma once
#include "../ecs/System.h"

class GhostSystem 
	: public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::GHOST);

    GhostSystem();

    ~GhostSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;
   
private:

    void generateGhosts();

    void moveGhosts();

    void destroyGhosts();


    bool pacManImmune = false;

    uint32_t ghostSpawnRate = 5000;
    uint32_t lastSpawn = 0;

    int followChance = 5;//sobre 1000
    float followFactor = 1.1f;

};

