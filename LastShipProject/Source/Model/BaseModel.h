#pragma once

#include "Base3DObject.h"

class BaseModel : Base3DObject
{
protected:
	int handle_m;
public:
	virtual void move() = 0;
	int getHandle(){ return handle_m; }
	BaseModel(){}
	virtual ~BaseModel(){}
};

