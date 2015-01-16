#pragma once

#include "BaseDxGame.h"

class LastShipGame : public BaseDxGame
{
private:
	int initialize();
	int finalize();
	int update();
	bool continues();
public:
	LastShipGame();
	~LastShipGame();
};

