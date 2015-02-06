#pragma once

#include "SceneChangeMethod.h"
#include "SceneTree.h"
#include "SceneFactory.h"

/*---------------------------------------------------------------------------------------
シーンの実行とシーンの移行,シーン生成クラスの管理をします。
テンプレート引数SceneIDはシーン識別名の型です。(列挙体や文字列など)

まずregisterScene<Scene>(id)を呼んで使用するシーンクラス(Scene)とそのシーンの識別名(id)を登録します。
そしてsetFirstScene(id)を呼んで最初のシーンを設定します。
メインループの中でexcuteScene()を実行します。
終わったらfinalize()を呼びます。
---------------------------------------------------------------------------------------*/
/*使用例
	SceneManager<projectj::SceneID> manager;
	
	manager.registerScene<projectj::SceneA>(projectj::SCENE_A);
	manager.registerScene<projectj::SceneB>(projectj::SCENE_B);
	manager.registerScene<projectj::SceneC>(projectj::SCENE_C);
	manager.setFirstScene(projectj::SCENE_A);

	while(true){
		if (manager.executeScene() != 0){
			break;
		}
	}

	manager.finalize();
*/

namespace projectj {
namespace scenemanager {

template<typename SceneID>
class SceneManager
{
private:
	typedef SceneTree<SceneID> Tree;
	typedef typename Tree::Iterator Iterator;
	typedef SceneFactory<SceneID> Factory;
	typedef typename SceneChangeMethodFactory<SceneID>::SceneChangeMethod SceneChangeMethod;
	Tree tree_m;
	Iterator currentScene_m;
	Factory factory_m;
private:
	SceneManager(const SceneManager &manager);
	SceneManager &operator=(const SceneManager &manager);
public:
	SceneManager() : currentScene_m(tree_m.end()) {}
	~SceneManager() {}
private:
	int changeScene();
public:
	template<typename DerivedScene>
	int registerScene(SceneID id);
	int executeScene();
	void finalize();
	int setFirstScene(SceneID id);
};


template<typename SceneID>
template<typename DerivedScene>
int SceneManager<SceneID>::registerScene(SceneID id)
{
	return factory_m.insertGenerator<DerivedScene>(id);
}

template<typename SceneID>
int SceneManager<SceneID>::changeScene()
{
	if(currentScene_m != tree_m.end()) {
		if(currentScene_m->scene_m == nullptr) { return -1; }
		SceneChangeMethod SceneChangeMethod
			= currentScene_m->scene_m->decideNext();

		currentScene_m = SceneChangeMethod->changeScene(
			factory_m, tree_m, currentScene_m);
	}

	if(currentScene_m == tree_m.end()) { return -1; }

	return 0;
}

template<typename SceneID>
int SceneManager<SceneID>::executeScene()
{
	if(currentScene_m == tree_m.end()) { return -1; }
	if(currentScene_m->scene_m == nullptr) { return -1; }
	if(currentScene_m->scene_m->execute() != 0) { return -1; }
	if(changeScene() != 0) { return -1; }

	return 0;
}

template<typename SceneID>
void SceneManager<SceneID>::finalize()
{
	currentScene_m = tree_m.end();
	tree_m.clear();
	factory_m.finalize();
}

template<typename SceneID>
int SceneManager<SceneID>::setFirstScene(SceneID id)
{
	currentScene_m = ResetScene<SceneID>(id).changeScene(factory_m, tree_m, currentScene_m);

	return 0;
}

}
}
