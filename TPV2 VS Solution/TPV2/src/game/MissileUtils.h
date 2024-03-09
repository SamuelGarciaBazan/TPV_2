#pragma once
#include "MissilesFacade.h"

class MissileUtils :
    public MissilesFacade
{
public:
    MissileUtils();
    ~MissileUtils();

    void remove_all_missiles() override;


    void createMisile() override;

};

