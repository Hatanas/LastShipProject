#pragma once

#include "SceneTree.h"
#include "SceneFactory.h"

/*---------------------------------------------------------------------------------------
シーンの実行とシーンの移行,シーン生成クラスの管理をします。
テンプレート引数SceneIDはシーン識別名の型です。(列挙体や文字列など)

まずregisterScene<Scene>(id)を呼んで使用するシーンクラス(Scene)とそのシーンの識別名(id)を登録します。
そしてsetFirstScene(id)を呼んで最初のシーンを設定します。
メインループの中でexcuteScene()を実行します。
終わったらfinalizeを呼びます。
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

template<typename SceneID>
class SceneManager
{	
private:
	typedef BaseScene<SceneID> Scene;
	typedef NextSceneInfo<SceneID> NextInfo;
	typedef SceneTree<SceneID> Tree;
	typedef typename Tree::Iterator Iterator;
	typedef SceneFactory<SceneID> Factory;

	Tree tree_m;
	Iterator currentScene_m;
	Factory factory_m;

	int changeScene();
private:
	SceneManager(const SceneManager &manager);
	SceneManager(const SceneManager &&manager);
	SceneManager &operator=(const SceneManager &manager);
	SceneManager &operator=(const SceneManager &&manager);
public:
	SceneManager() : currentScene_m(tree_m.end()){}
	~SceneManager(){}
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
	NextInfo nextInfo;
	Scene *scene;

	if (currentScene_m != tree_m.end()){
		nextInfo = currentScene_m->scene_m->decideNextScene();

		switch (nextInfo.wayToChange_m){
		case KEEP:
			break;
		case CLEAR:
			currentScene_m = tree_m.clearScene();
			break;
		case POP:
			currentScene_m = tree_m.popScene(nextInfo.nextID_m, currentScene_m);
			break;
		case RESET:
			scene = factory_m.getScene(nextInfo.nextID_m);
			currentScene_m = tree_m.resetScene(nextInfo.nextID_m, scene);
			break;
		case PUSH:
			scene = factory_m.getScene(nextInfo.nextID_m);
			currentScene_m = tree_m.pushScene(nextInfo.nextID_m, currentScene_m, scene);
			break;
		case JUMP:
			scene = factory_m.getScene(nextInfo.nextID_m);
			currentScene_m = tree_m.jumpScene(nextInfo.nextID_m, currentScene_m, scene);
			break;
		case PARENT:
			currentScene_m = tree_m.parentScene(nextInfo.nextID_m, currentScene_m);
			break;
		case CHILD:
			currentScene_m = tree_m.childScene(nextInfo.nextID_m, currentScene_m);
			break; 
		default:
			currentScene_m = tree_m.end();
			break;
		}
	}

	if (currentScene_m == tree_m.end()){ return -1; }

	return 0;
}

template<typename SceneID>
int SceneManager<SceneID>::executeScene()
{
	if (currentScene_m == tree_m.end()){ return -1; }
	if (currentScene_m->scene_m == nullptr){ return -1; }
	if (currentScene_m->scene_m->inputUpdateOutput() != 0){ return -1; }
	if (changeScene() != 0){ return -1; }
	return 0;
}

template<typename SceneID>
void SceneManager<SceneID>::finalize()
{
	currentScene_m = tree_m.clearScene();
	tree_m.clear();
	factory_m.finalize();
}

template<typename SceneID>
int SceneManager<SceneID>::setFirstScene(SceneID id)
{
	Scene *firstScene = factory_m.getScene(id);

	if (firstScene == nullptr){ return -1; }
	currentScene_m = tree_m.resetScene(id, firstScene);

	return 0;
}
