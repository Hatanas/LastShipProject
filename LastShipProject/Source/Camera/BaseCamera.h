#pragma once
class BaseCamera
{
public:
	virtual void apply() = 0;
	virtual void move() = 0;
	BaseCamera(){}
	virtual ~BaseCamera(){}
};

