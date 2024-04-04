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

    void movePacMan();

    void resetPos();
    void resetLifes();

    ecs::entity_t pacMan;

    float pacManVel = 3.f;

    bool leftPressed = false;
    bool rightPressed = false;

    int pacmanWidth = 40;
    int pacmanHeight = 40;
};

