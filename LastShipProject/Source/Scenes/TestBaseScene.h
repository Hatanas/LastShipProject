#pragma once

#include "./../SceneManager/BaseScene.h"
#include "TestSceneID.h"
#include <string>
#include <iostream>

namespace scenetest {

class TestBaseScene : public projectj::scenemanager::BaseScene<scenetest::TestSceneID>
{
protected:
	std::string name_m = "TestBaseScene";
private:
	int method_m;
	ID id_m;
public:
	TestBaseScene();
	virtual ~TestBaseScene();
public:
	int finalize();
	int initialize();
	int execute();
	ChangeMethod decideNext();
};

}

