#pragma once
#include "../ecs/System.h"


class ImmunitySystem
	: public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::IMMUNITY);

    ImmunitySystem();

    ~ImmunitySystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:

    void updateImmnunity();

    uint32_t immunityTime;
    uint32_t timeStart;

    bool isImmune = false;

};

