#include "Gun.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "Transform.h"
#include "Image.h"

Gun::Gun()
{
	bulletTexture = &sdlutils().images().at("fire");
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
			if (bullet.pos.getX() < (0 - 5) || bullet.pos.getX() > sdlutils().width() ||
				bullet.pos.getY() < (0 - 20) || bullet.pos.getY() > sdlutils().height()) {
				bullet.used = false;
			}
		}
	}

	if (ih().isKeyDown(SDL_SCANCODE_S) && (lastShoot+fireRate) < sdlutils().virtualTimer().currTime()) {
		
		sdlutils().soundEffects().at("fire");

		lastShoot = sdlutils().virtualTimer().currTime();

		auto& pos = myTransform->getPos();
		auto& vel = myTransform->getVel();
		auto h = myTransform->getHeight();
		auto w = myTransform->getWidth();
		auto r = myTransform->getRot();

		auto c = pos + Vector2D(w / 2.0f, h / 2.0f);

		int bwidth = 5;
		int bheight = 20;
		 
		Vector2D bp = c - Vector2D(bwidth / 2 , h / 2.0f + 5.0f + bheight).rotate(r) - Vector2D(bwidth / 2, bheight / 2);

		//bp = c;

		Vector2D bv = Vector2D(0, -1).rotate(r) * (vel.magnitude() + 5.0f);

		shoot(bp, bv, bwidth, bheight, Vector2D(0, -1).angle(bv));

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
	myImage = mngr_->getComponent<Image>(ent_);
	myTransform = mngr_->getComponent<Transform>(ent_);
	myTransform->setWidth(myImage->getTexture().width());
	myTransform->setHeight(myImage->getTexture().height());

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

	lastUsed = (lastUsed + 1) % bullets_.size();
}
