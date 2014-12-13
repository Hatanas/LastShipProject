#pragma once

#include "DxLib.h"
#include <map>
#include <algorithm>
#include "./../utility/CSVReader.h"

//1��ڂ�3D���f���̖��O, 2��ڂ�3D���f���̃p�X�������ꂽcsv�t�@�C����ǂݍ����
//3D���f�����������Ƀ��[�h��, 3D���f�����ƃ��[�h�������f���̃n���h���̑Ή��\������N���X�ł��B
//3D���f�������w�肵�Ă���3D���f�����R�s�[��, ���̃n���h���𓾂邱�Ƃ��ł��܂��B

//�g����
//model_load_data.csv
/*
Sample,material/3D_model/sample_3Dmodel/sample_3Dmodel.mqo
Skydome,material/3D_model/skydome/skydome.mqo
*/
//main.cpp
/*
#include "DxLib.h"
#include "ModelFactory.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1){ return -1; }//dxlib�̏���������

	ModelFactory factory("data/model_load_data.csv");
	int skydome = factory.getHandle("Skydome");
	int sample = factory.getHandle("Sample");

	DrawFormatString(0, 0, 0xffffff, "%d0,%d", skydome, sample);
	MV1DrawModel(skydome);
	MV1DrawModel(sample);
	ScreenFlip();
	WaitKey();

	DxLib_End();// �c�w���C�u�����̏I������

	return 0;
}
*/

class ModelFactory
{
public:
	typedef CSVReader::CSVTable CSVTable;
private:
	std::map<std::string, int> mapNameHandle_m;
	bool readCSV(const std::string &csvFilePath, CSVTable &table);
	int loadModels(CSVTable &table);
	int resizeTable(CSVTable &table);
public:
	int createMap(const std::string &filePath);
	int getHandle(const std::string &modelName);
	void clearMap(){ mapNameHandle_m.clear(); }
	ModelFactory(){}
	ModelFactory(std::string filePath){ createMap(filePath); }
	~ModelFactory(){}
};

