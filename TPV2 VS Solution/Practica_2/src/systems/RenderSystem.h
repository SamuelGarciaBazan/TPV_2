#pragma once
#include "../ecs/System.h"

class RenderSystem
	:public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::RENDER);

    RenderSystem();

    ~RenderSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:

    void renderFruits();

    void renderGhosts();

    void renderPacman();



};

