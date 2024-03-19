#pragma once
class Vector2D;

class BlackHolesFacade {
public:
	BlackHolesFacade() {}
	virtual ~BlackHolesFacade() {}
	virtual void create_black_holes(int n) = 0;
	virtual void remove_all_black_holes() = 0;

private:
	virtual void create_black_hole(Vector2D pos) = 0;
};