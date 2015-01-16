#include "LastShipGame.h"

int LastShipGame::update()
{
	if(CheckHitKey(KEY_INPUT_RETURN) != 0) { finish(); }

	return 0;
}

int LastShipGame::initialize()
{
	ChangeWindowMode(TRUE);
	if(DxLib_Init() < 0) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	
	return 0;
}

int LastShipGame::finalize()
{
	DxLib_End();

	return 0;
}

bool LastShipGame::continues()
{
	return !hasFinished()
		&& CheckHitKey(KEY_INPUT_ESCAPE) == 0;
}

LastShipGame::LastShipGame() {}

LastShipGame::~LastShipGame() {}
