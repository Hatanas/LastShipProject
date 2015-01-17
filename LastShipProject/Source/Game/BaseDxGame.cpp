#include "BaseDxGame.h"

int BaseDxGame::play()
{
	if(initialize() != 0) { return -1; }

	while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		if(continues()) {
			if(update() != 0) { return -1; }
		}
		else { break; }
	}

	finalize();

	return 0;
}

void BaseDxGame::finish() { hasFinished_m = true; }

bool BaseDxGame::hasFinished() { return hasFinished_m; }
