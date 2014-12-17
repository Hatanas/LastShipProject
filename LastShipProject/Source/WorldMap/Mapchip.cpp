#include "Mapchip.h"

Mapchip::Mapchip(
	int modelHandle,
	int vertexShaderHandle,
	int pixelShaderHandle,
	std::string modelName,
	std::string vertexShaderName,
	std::string pixelShaderName,
	std::string eventName,
	std::string mapchipName,
	int indexI,
	int indexJ
	)
{
	this->modelHandle = modelHandle;
	this->vertexShaderHandle = vertexShaderHandle;
	this->pixelShaderHandle = pixelShaderHandle;
	this->modelName = modelName;
	this->vertexShaderName = vertexShaderName;
	this->pixelShaderName = pixelShaderName;
	this->eventName = eventName;
	this->mapchipName = mapchipName;
	this->indexI = indexI;
	this->indexJ = indexJ;
}