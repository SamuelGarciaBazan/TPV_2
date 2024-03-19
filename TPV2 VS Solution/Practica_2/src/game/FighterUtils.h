#pragma once
#include "FighterFacade.h"

class Transform;
class Health;
class Image;
class Gun;


class FighterUtils :
    public FighterFacade
{
public:
    FighterUtils(){};
    ~FighterUtils(){};

    void create_fighter() override;
    void  reset_fighter() override;
    void  reset_lives() override;
    int  update_lives(int n) override;


private:
    Transform* transform;
    Health* health;
    Image* image;
    Gun* gun;

};

