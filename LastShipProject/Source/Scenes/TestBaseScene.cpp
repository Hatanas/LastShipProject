#include "TestBaseScene.h"

using scenetest::TestBaseScene;
using namespace projectj::scenemanager;

TestBaseScene::TestBaseScene() {}

TestBaseScene::~TestBaseScene() {}

int TestBaseScene::finalize()
{
	std::cout << name_m << "::finalize()" << std::endl;
	return 0;
}

int TestBaseScene::initialize()
{
	std::cout << name_m << "::initialize()" << std::endl;
	return 0;
}

int TestBaseScene::execute()
{
	std::cout << name_m << "::execute()" << std::endl;

	std::cout << "way (0:KEEP/ 1:CLEAR/ 2:POP/ 3:RESET/ 4:PUSH/ 5:JUMP/ 6:PARENT/ 7:CHILD)-->";
	std::cin >> method_m;
	if(method_m < 0 || 7 < method_m) { return -1; }

	std::cout << "id (0:NULL/ 1:A/ 2:B/ 3:C)-->";
	int id; std::cin >> id;
	if(id < 0 || 3 < id) { return -1; }
	id_m = static_cast<TestSceneID>(id);

	return 0;
}

TestBaseScene::ChangeMethod scenetest::TestBaseScene::decideNext()
{
	ChangeMethod method;
	std::cout << name_m << "::decideNext()" << std::endl;
	switch(method_m) {
	case 0:
		method = MethodFactory::get<KeepScene<ID>>(id_m);
		break;
	case 1:
		method = MethodFactory::get<ClearScene<ID>>(id_m);
		break;
	case 2:
		method = MethodFactory::get<PopScene<ID>>(id_m);
		break;
	case 3:
		method = MethodFactory::get<ResetScene<ID>>(id_m);
		break;
	case 4:
		method = MethodFactory::get<PushScene<ID>>(id_m);
		break;
	case 5:
		method = MethodFactory::get<JumpScene<ID>>(id_m);
		break;
	case 6:
		method = MethodFactory::get<ParentScene<ID>>(id_m);
		break;
	case 7:
		method = MethodFactory::get<ChildScene<ID>>(id_m);
		break;
	default:
		method = MethodFactory::get<BaseSceneChangeMethod<ID>>(id_m);
		break;
	}

	return method;
}
