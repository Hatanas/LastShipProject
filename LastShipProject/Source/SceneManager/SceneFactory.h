#pragma once

#include "SceneIDGeneratorMap.h"

//---------------------------------------------------------------------------------------
//機能, 役割         : シーンの生成をします。
//---------------------------------------------------------------------------------------

namespace projectj {
namespace scenemanager {

template<typename SceneID>
class SceneFactory
{
private:
	typedef BaseScene<SceneID> Scene;
	typedef BaseSceneGenerator<SceneID> Generator;
	typedef typename Generator::SharedScene SharedScene;
	typedef SceneIDGeneratorMap<SceneID> IDGeneratorMap;

	IDGeneratorMap idGeneratorMap_m;
private:
	SceneFactory(const SceneFactory &factory);
	SceneFactory &operator=(const SceneFactory &factory);
public:
	SceneFactory() {}
	~SceneFactory() {}
public:
	SharedScene getScene(SceneID id) const;
	void finalize();
	template<class DerivedScene>
	int insertGenerator(SceneID id);
};

template<typename SceneID> template<class DerivedScene>
int SceneFactory<SceneID>::insertGenerator(SceneID id)
{
	return idGeneratorMap_m.insertGenerator<DerivedScene>(id);
}

template<typename SceneID>
void SceneFactory<SceneID>::finalize()
{
	idGeneratorMap_m.clearMap();
}

template<typename SceneID>
typename SceneFactory<SceneID>::SharedScene SceneFactory<SceneID>::getScene(SceneID id) const
{
	Generator *generator = nullptr;
	SharedScene newScene = nullptr;

	generator = idGeneratorMap_m.getGenerator(id);
	if(generator != nullptr) {
		newScene = generator->generateScene();
	}

	return newScene;
}

}
}