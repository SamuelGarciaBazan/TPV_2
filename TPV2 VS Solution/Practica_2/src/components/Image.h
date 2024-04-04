#pragma once
#include "../ecs/Component.h"

#include <string>


class Texture;
class Transform;

class Image :
    public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::IMAGE);

    Image(std::string id, int fils, int cols);
    ~Image();

    void render() override;

    void initComponent() override;

    Texture& getTexture() { return *myTexture; }

//private:, ahora es public

    Texture* myTexture;
    Transform* myTransform;


    int fils;
    int cols;

    int frameWidth;
    int frameHeight;

    int currentFrame = 26;
};

