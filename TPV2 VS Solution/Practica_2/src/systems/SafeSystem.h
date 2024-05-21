#pragma once


#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"


class SafeSystem
    :public ecs::System
{

public:
    __SYSID_DECL__(ecs::sys::SAFE);

    SafeSystem();

    ~SafeSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:


    void checkIsSafe();

    bool safeMode = false;



    int safeDistance = 200;//para testearmejor

    uint32_t startTimeInDanger;
    uint32_t dangerTime = 2000;

    uint32_t startSafeMode;
    uint32_t safeModeTime = 2000;

    void updateSafeMode();
};

