#pragma once

#include <algorithm>
#include "../../Tree.h"
#include "..\BaseScene\BaseScene.h"

template<typename SceneID>
struct SceneNode
{
	SceneID id_m;
	BaseScene<SceneID> *scene_m;
	bool operator==(const SceneNode scene)const{ return id_m == scene.id_m; }
	bool operator!=(const SceneNode scene)const{ return id_m != scene.id_m; }
	bool operator<=(const SceneNode scene)const{ return id_m <= scene.id_m; }
	bool operator>=(const SceneNode scene)const{ return id_m >= scene.id_m; }
	bool operator<(const SceneNode scene)const{ return id_m < scene.id_m; }
	bool operator>(const SceneNode scene)const{ return id_m > scene.id_m; }
};


template<typename SceneID>
class SceneTree : public Tree<SceneNode<SceneID>>
{
public:
	typedef BaseScene<SceneID> Scene;
	typedef SceneNode<SceneID> Node;
	typedef typename SceneTree<SceneID>::pre_order_iterator Iterator;
private:
	SceneTree(const SceneTree &tree);
	SceneTree &operator=(const SceneTree &tree);
	void deleteScene(Iterator iterator);
public:
	Iterator clearScene();
	Iterator popScene(SceneID id, Iterator current);
	Iterator resetScene(SceneID id, Scene *scene);
	Iterator pushScene(SceneID id, Iterator current, Scene *scene);
	Iterator jumpScene(SceneID id, Iterator current, Scene *scene);
	Iterator childScene(SceneID id, Iterator current);
	Iterator parentScene(SceneID id, Iterator current);
	SceneTree(){}
	~SceneTree(){}
};

template<typename SceneID>
void SceneTree<SceneID>::deleteScene(Iterator iterator)
{
	if (empty()){ return; }

	Iterator begin = iterator, end = iterator;
	auto Delete = [](Node &node)
	{
		if (node.scene_m != nullptr){
			node.scene_m->finalize();
			delete node.scene_m;
			node.scene_m = nullptr;
		}
	};

	while (!end.isLeaf()){ end.goLastChild(); }
	std::for_each(begin, ++end, Delete);
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::clearScene()
{
	deleteScene(begin());
	clear();
	return end();
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::popScene(
	SceneID id, Iterator current)
{
	if (current == end()){ return end(); }
	
	Iterator target = current;

	current.goParent();
	deleteScene(target);
	erase(target);

	return current;
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::resetScene(
	SceneID id, Scene *scene)
{
	clearScene();
	scene->initialize();
	return insert_root({ id, scene });
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::pushScene(
	SceneID id, Iterator current, Scene *scene)
{
	if (scene == nullptr){ return end(); }

	Node sceneNode = { id, scene };
	
	if (insert_child(current, sceneNode) == end()){
		return end();
	}

	scene->initialize();
	
	return find(sceneNode);
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::jumpScene(
	SceneID id, Iterator current, Scene *scene)
{
	Iterator iterator
		= std::find_if(begin(), end(), [id](const SceneNode<SceneID> node)->bool
	{
		return id == node.id_m;
	});

	if (iterator == end()){
		iterator = pushScene(id, current, scene);
	}
	else{
		delete scene;
		scene = nullptr;
	}

	return iterator;
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::parentScene(
	SceneID id, Iterator current)
{
	if (current.isRoot() || current == end()){
		return end();
	}
	current.goParent();

	return current;
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::childScene(
	SceneID id, Iterator current)
{
	if (current.isLeaf()){ return end(); }

	Iterator firstChild = current;
	firstChild.goFirstChild();

	while (true){
		if (firstChild->id_m == id){ break; }
		else{
			if (firstChild.isLast()){ return end(); }
			firstChild.goNextSibling();
		}
	}

	return firstChild;
}


