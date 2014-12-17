#pragma once

#include <string>

class Mapchip
{
protected:
	int modelHandle;
	int vertexShaderHandle;
	int pixelShaderHandle;
	std::string modelName;
	std::string vertexShaderName;
	std::string pixelShaderName;
	std::string eventName;
	std::string mapchipName;
	int indexI;
	int indexJ;

public:
	Mapchip(
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
		);
	~Mapchip() {}

public:
	int getModelHandle() { return modelHandle; }
	int getVertexShaderHandle() { return vertexShaderHandle; }
	int getPixelShaderHandle() { return pixelShaderHandle; }
	std::string getModelName() { return modelName; }
	std::string getVertexShaderName() { return vertexShaderName; }
	std::string getPixelShaderName() { return pixelShaderName; }
	std::string getEventName() { return eventName; }
	std::string getMapchipName() { return mapchipName; }
	int getIndexI() { return indexI; }
	int getIndexJ() { return indexJ; }
};