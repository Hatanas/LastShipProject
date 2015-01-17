#pragma once

#include <cassert>
#include "DxLib.h"
#include "GameInterface.h"

class BaseDxGame : public GameInterface
{
private:
	bool hasFinished_m = false;
protected:
	virtual int initialize() = 0;
	virtual int finalize() = 0;
	virtual int update() = 0;
	virtual bool continues() = 0;
	void finish();
	bool hasFinished();
public:
	int play();
	BaseDxGame() {}
	virtual ~BaseDxGame() {}
};

