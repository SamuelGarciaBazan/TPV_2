#pragma once

#include "BlackHolesFacade.h"

class BlackHolesUtils : public BlackHolesFacade
{
public:
	BlackHolesUtils();
	~BlackHolesUtils();
	
	void create_black_holes(int n) override;
	void remove_all_black_holes() override;

private:
	void create_black_hole(Vector2D pos) override;

};

