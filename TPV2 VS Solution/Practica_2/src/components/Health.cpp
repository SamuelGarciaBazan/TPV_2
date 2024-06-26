#include "Health.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

Health::Health(std::string name,float scale) 
	:scale(scale)
{
	healthTexture = &sdlutils().images().at(name);
	offSetX = healthTexture->width() * scale;

	maxLifes = sdlutils().gameConstants().at("pacManMaxLifes");
	currentLifes = maxLifes;
}

Health::~Health()
{
}

void Health::render()
{
	Vector2D pos;
	for (int i = 0; i < currentLifes; i++) {
		pos.set(initialX + (offSetX * i), initialY);
		healthTexture->render(build_sdlrect(pos, healthTexture->width()*scale, healthTexture->height()* scale));
	}
	
}
