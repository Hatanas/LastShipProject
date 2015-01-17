#include "BaseAnimation.h"


BaseAnimation::BaseAnimation(float interval, float maxIndex)
	:interval_m(interval), max_m(maxIndex)
{
	assert(interval_m > 0.0f && max_m >= 0.0f);
}

BaseAnimation::~BaseAnimation(){}

void BaseAnimation::start()
{
	isValid_m = true;
	index_m = 0.0f;
}

void BaseAnimation::stop()
{
	isValid_m = false;
	index_m = 0.0f;
}

float BaseAnimation::getIndex()const
{
	return index_m;
}

void BaseAnimation::update()
{
	if(!isValid()) { return; }

	if((index_m += interval_m) > max_m) {
		index_m = 0.0f;
	}
}

bool BaseAnimation::isValid()const
{
	return isValid_m;
}
