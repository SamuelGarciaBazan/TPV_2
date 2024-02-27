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

    Image(std::string key);
    ~Image();

    void render() override;

    void initComponent() override;

private:

    Texture* myTexture;
    Transform* myTransform;

};

