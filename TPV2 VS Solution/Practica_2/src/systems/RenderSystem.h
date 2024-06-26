#pragma once
#include "../ecs/System.h"

class ImageWithFrames;

class RenderSystem
	:public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::RENDER);

    RenderSystem();

    ~RenderSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:

    void renderFruits();

    void renderGhosts();

    void renderPacman();

    void renderLifes();

    void renderImageWithFrames(ImageWithFrames*);
    void updateImageWithFrames(ImageWithFrames*);

    void updateGhostsImmunityON(ImageWithFrames*);

    void immunityStart();
    void immunityEnd();

    bool pacManImmune = false;

    int firstIndexImmunityGhost = 30;
    int lastIndexImmunityGhost = 31;

};

