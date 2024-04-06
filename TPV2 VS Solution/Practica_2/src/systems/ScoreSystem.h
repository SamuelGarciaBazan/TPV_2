#pragma once

#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"

class Font;

class ScoreSystem
	:public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::SCORE);

    ScoreSystem();

    ~ScoreSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:

    Font* font;

    int currentScore = 0;

    int foodScore = 10;

    int ghostScore = 100;

    SDL_Rect destinationRect;
    
    SDL_Color textColor;

    void renderText();
};

