#pragma once

#include "BaseAnimation.h"

class DerivedAnimation :
	public BaseAnimation
{
public:
	float getTime() { return getIndex(); }
	DerivedAnimation(float interval, float maxIndex);
	~DerivedAnimation();
};

