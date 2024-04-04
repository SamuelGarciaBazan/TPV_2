#pragma once
#include "../ecs/Component.h"

#include <string>


class MiracleFruit
	:public ecs::Component
{
public:

    __CMPID_DECL__(ecs::cmp::MIRACLEFRUIT);

    MiracleFruit(std::string id, int fils, int cols);
    ~MiracleFruit();

    void update() override;

    void render() override;

    void initComponent() override;

    void resetTimer();

    void startMiracle();

    uint32_t minCooldown = 10000;
    uint32_t maxCooldown = 20000;
    uint32_t minDuration = 1000;
    uint32_t maxDuration = 5000;

    uint32_t miracleCooldown;
    uint32_t miracleDuration;

    uint32_t startTime;

    bool miracleON = false;


};

