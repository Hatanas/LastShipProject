#pragma once

#include "./../Model/BaseModel.h"
#include "DxLib.h"

class DrawingModel
{
	int modelHandle_m = -1;
public:
	DrawingModel();
	DrawingModel(BaseModel *model);
	DrawingModel(int handle);
	void setModel(int handle);
	void setModel(BaseModel *model);
	void draw();
	~DrawingModel();
};

