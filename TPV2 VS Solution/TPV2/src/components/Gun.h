#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"


#include <array>

class Transform;


class Gun :
    public ecs::Component
{
public:

    __CMPID_DECL__(ecs::cmp::GUN);

    Gun();
    ~Gun();

    void update() override;
    void render() override;
    void initComponent() override;

    struct Bullet {
        bool used = false;
        Vector2D pos;
        Vector2D vel;
        int width;
        int height;
        float rot;
    };

    constexpr static auto max_bullets = 20;
    typedef std::array<Bullet, max_bullets> bullets_array;
    typedef bullets_array::iterator iterator;
   

    void reset(){for(auto& b :bullets_) b.used = false; };
 
    iterator begin() {
        return bullets_.begin();
    }
    iterator end() {
        return bullets_.end();
    }
    
   
private:
    void shoot(Vector2D p, Vector2D v, int width, int height, float r);
    bullets_array bullets_;

    Texture* bulletTexture;
   

    int lastUsed = 0;

    Transform* myTransform;
};


