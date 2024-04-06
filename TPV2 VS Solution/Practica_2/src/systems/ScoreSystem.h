#pragma once

#include "../ecs/System.h"


class ScoreSystem
	:public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::SCORE);

    ScoreSystem();

    ~ScoreSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:

};

