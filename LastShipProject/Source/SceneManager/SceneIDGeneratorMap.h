#pragma once

#include <map>
#include <algorithm>
#include "SceneGenerator.h"

//---------------------------------------------------------------------------------------
//機能, 役割         : シーン識別列挙定数とシーン生成クラスの対応(写像)を管理します。
//注意               : 静的なメンバ変数, メンバ関数を使用しています。
//                   : addGeneratorで追加したシーン生成クラスはclearMapでdeleteされます。
//---------------------------------------------------------------------------------------

namespace projectj {
namespace scenemanager {

template<typename SceneID>
class SceneIDGeneratorMap
{
private:
	typedef BaseSceneGenerator<SceneID> Generator;
	typedef std::map<SceneID, Generator *> MapIDGenerator;
	typedef std::pair<SceneID, Generator *> PairIDGenerator;
	MapIDGenerator map_m;

	SceneIDGeneratorMap(const SceneIDGeneratorMap &generator);
	SceneIDGeneratorMap &operator=(const SceneIDGeneratorMap &generator);
public:
	SceneIDGeneratorMap() {}
	~SceneIDGeneratorMap() {}
	template<class Scene>
	int insertGenerator(SceneID id);
	int insertGenerator(SceneID id, Generator *generator);
	void clearMap();
	Generator *getGenerator(SceneID &id) const;
};

template<typename SceneID> template<class Scene>
int SceneIDGeneratorMap<SceneID>::insertGenerator(SceneID id)
{
	return insertGenerator(id, new SceneGenerator<SceneID, Scene>());
}

template<typename SceneID>
int SceneIDGeneratorMap<SceneID>::insertGenerator(
	SceneID id, Generator *generator)
{
	if(generator == nullptr) { return -1; }
	if(map_m.find(id) != map_m.end()) { return -1; }
	map_m.insert(std::make_pair(id, generator));
	//map_m.[id] = generator;

	return 0;
}

template<typename SceneID>
void SceneIDGeneratorMap<SceneID>::clearMap()
{
	std::for_each(map_m.begin(), map_m.end(), [](PairIDGenerator pair)
	{
		delete pair.second;
		pair.second = nullptr;
	});
	map_m.clear();
}

template<typename SceneID>
typename SceneIDGeneratorMap<SceneID>::Generator *
	SceneIDGeneratorMap<SceneID>::getGenerator(SceneID &id) const
{
	if(map_m.find(id) == map_m.end()) { return nullptr; }

	return map_m.at(id);
}

}
}
