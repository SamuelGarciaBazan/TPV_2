#pragma once
#include "../ecs/System.h"

class PacManSystem :
    public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::PACMAN);

    PacManSystem();
    ~PacManSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:

    ecs::entity_t pacMan;

    void animatePacMan();

    float pacManVel = 1.f;

    uint32_t inputDelay = 500u;
    uint32_t lastInput = 0u;

};
