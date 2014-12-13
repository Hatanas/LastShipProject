#pragma once

#include "./../Model/BaseModel.h"
#include "DxLib.h"

class DrawingModel
{
	int modelHandle_m = -1;
public:
	DrawingModel();
	DrawingModel(BaseModel *model){ setModel(model->getHandle()); }
	DrawingModel(int handle){ setModel(handle); }
	void setModel(int handle){ modelHandle_m = handle; }
	void setModel(BaseModel *model){ modelHandle_m = model->getHandle(); }
	void draw(){
		MV1DrawModel(modelHandle_m);
	}
	~DrawingModel();
};

