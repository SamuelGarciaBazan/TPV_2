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

};

