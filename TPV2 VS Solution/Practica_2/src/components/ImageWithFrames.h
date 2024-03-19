#pragma once
#include "../ecs/Component.h"
#include<iostream>
#include<cstdint>


class Texture;
class Transform;

class ImageWithFrames :
    public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::IMAGEWITHFRAMES);

    ImageWithFrames(std::string id,int fils,int cols);
    ~ImageWithFrames();

    void update() override;

    void render() override;

    void initComponent() override;

private:
    Texture* myTexture;
    int fils;
    int cols;

    int frameWidth;
    int frameHeight;

    int currentFrame = 26;

    uint32_t lastFrame = 0 ;
    uint16_t frameTime = 50 ;

    Transform* myTransform;
};

