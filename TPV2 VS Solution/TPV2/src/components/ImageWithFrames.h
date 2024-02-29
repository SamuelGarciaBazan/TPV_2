#pragma once
#include "../ecs/Component.h"
#include<iostream>

class Texture;

class ImageWithFrames :
    public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::IMAGEWITHFRAMES);

    ImageWithFrames(std::string id,int fils,int cols);
    ~ImageWithFrames();

    void update() override;

private:
    Texture* myTexture;
    int fils;
    int cols;

    int currentFrame = 0;
};

