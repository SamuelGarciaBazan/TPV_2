#include "Gun.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "Transform.h"

Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::update()
{
	//update de las balas
	for (auto& bullet : bullets_) {
		if (bullet.used) {

			//actualizar la posicion
			bullet.pos = bullet.pos + bullet.vel;

			//si sale de la pantalla poner en false???
		}
	}

	
	//falta condicion de tiempo
	if (ih().isKeyDown(SDL_SCANCODE_S)) {
		
		sdlutils().soundEffects().at("fire");

	}
	/*
	int bh = 20;
	Vector2D c = myTransform->getPos() + Vector2D(w / 2.0f, h / 2.0f);
	Vector2D bp = c - Vector2D(bw / 2, h / 2.0f + 5.0f + bh).rotate(myTransform->getRot()) - Vector2D(bw / 2, bh / 2);
	Vector2D bv = Vector2D(0, -1).rotate(myTransform->getRot()) * (myTransform->getVel().magnitude() + 5.0f);
	float br = Vector2D(0, -1).angle(bv);
	*/
	

}

void Gun::render()
{
	for (auto& bullet : bullets_) {
		if (bullet.used) {

			bulletTexture->render(build_sdlrect(bullet.pos, bullet.width, bullet.height),bullet.rot);
		}
	}
}

void Gun::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);

}

void Gun::shoot(Vector2D p, Vector2D v, int width, int height, float r)
{
	while (bullets_[lastUsed].used) lastUsed = (lastUsed + 1) % bullets_.size();

	auto bullet = &bullets_[lastUsed];
	
	bullet->used = true;
	bullet->pos = p;
	bullet->vel = v;
	bullet->width = width;
	bullet->height = height;
	bullet->rot = r;


}
