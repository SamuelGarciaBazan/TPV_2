#include "MiracleFruit.h"
#include "../sdlutils/SDLUtils.h"


MiracleFruit::MiracleFruit()
{
	minCooldown = sdlutils().gameConstants().at("miracleMinCooldown");
	maxCooldown = sdlutils().gameConstants().at("miracleMaxCooldown");

	minDuration = sdlutils().gameConstants().at("miracleMinDuration");
	maxDuration = sdlutils().gameConstants().at("miracleMaxDuration");




	miracleCooldown = sdlutils().rand().nextInt(minCooldown, maxCooldown);

	resetTimer();
}

MiracleFruit::~MiracleFruit()
{
}

void MiracleFruit::update()
{
}

void MiracleFruit::render()
{
}

void MiracleFruit::initComponent()
{
}

void MiracleFruit::resetTimer()
{
	startTime = sdlutils().virtualTimer().currTime();
	miracleON = false;
}

void MiracleFruit::startMiracle()
{
	startTime = sdlutils().virtualTimer().currTime();
	miracleDuration = sdlutils().rand().nextInt(minDuration, maxDuration);
	miracleON = true;

}

