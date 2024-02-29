#pragma once
#include "../ecs/Component.h"


class Generations :
    public ecs::Component
{
public:

    __CMPID_DECL__(ecs::cmp::GENERATIONS);

    Generations(int n);
    ~Generations();

private:

    int currentGenerations;

    int getGenerations() { return currentGenerations; }

    void setGenerations(int n) { currentGenerations = n; }

};

