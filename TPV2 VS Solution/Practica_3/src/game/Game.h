// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once


class LittleWolf;

class Game {
public:
	Game();
	virtual ~Game();
	bool init(const char* host, int port);
	void start();

	static Game* _instance;

	static Game* instance(){return _instance;};

private:
	LittleWolf *little_wolf_;

};

