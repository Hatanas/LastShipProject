#pragma once

#include <map>
#include <algorithm>
#include "SceneGenerator.h"

//---------------------------------------------------------------------------------------
//�@�\, ����         : �V�[�����ʗ񋓒萔�ƃV�[�������N���X�̑Ή�(�ʑ�)���Ǘ����܂��B
//����               : �ÓI�ȃ����o�ϐ�, �����o�֐����g�p���Ă��܂��B
//                   : addGenerator�Œǉ������V�[�������N���X��clearMap��delete����܂��B
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
