#pragma once

class Vector2D;

class MissilesFacade {
public:
	MissilesFacade() {}
	virtual ~MissilesFacade() {}

	virtual void createMisile() = 0;

	virtual void remove_all_missiles() = 0;
};
