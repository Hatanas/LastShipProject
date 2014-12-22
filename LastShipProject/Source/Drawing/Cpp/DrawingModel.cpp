#include "../DrawingModel.h"

inline DrawingModel::DrawingModel(){}

inline DrawingModel::DrawingModel(BaseModel *model)
{
	setModel(model->getHandle()); 
}

inline DrawingModel::DrawingModel(int handle)
{
	setModel(handle);
}

inline void DrawingModel::setModel(int handle)
{
	modelHandle_m = handle; 
}

inline void DrawingModel::setModel(BaseModel *model)
{
	setModel(model->getHandle());
}

inline void DrawingModel::draw()
{
	MV1DrawModel(modelHandle_m);
}

inline DrawingModel::~DrawingModel(){}