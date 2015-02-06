#pragma once

#include <algorithm>
#include "../Utility/Tree/Tree.h"
#include "BaseScene.h"


namespace projectj {
namespace scenemanager {
template<typename SceneID>
class BaseScene;

template<typename SceneID>
struct SceneNode
{
	typedef BaseScene<SceneID> Scene;
	typedef std::shared_ptr<Scene> SharedSene;

	SceneID id_m;
	SharedSene scene_m;

	bool operator==(const SceneNode scene)const { return id_m == scene.id_m; }
	bool operator!=(const SceneNode scene)const { return id_m != scene.id_m; }
	bool operator<=(const SceneNode scene)const { return id_m <= scene.id_m; }
	bool operator>=(const SceneNode scene)const { return id_m >= scene.id_m; }
	bool operator<(const SceneNode scene)const { return id_m < scene.id_m; }
	bool operator>(const SceneNode scene)const { return id_m > scene.id_m; }
};


template<typename SceneID>
class SceneTree
{
private:
public:
	typedef SceneNode<SceneID> Node;
	typedef typename Node::SharedSene SharedScene;
	typedef typename Tree<SceneNode<SceneID>>::pre_order_iterator Iterator;
private:
	Tree<SceneNode<SceneID>> sceneTree_m;
public:
	SceneTree() {}
	~SceneTree() {}
private:
	SceneTree(const SceneTree &tree) = delete;
	SceneTree(const SceneTree &&tree) = delete;
	SceneTree &operator=(const SceneTree &tree) = delete;
	SceneTree &operator=(const SceneTree &&tree) = delete;
public:
	void deleteScene(Iterator iterator);
	void erase(Iterator pos);
	Iterator begin()const;
	Iterator end()const;
	void clear();
	Iterator insertRoot(Node const &node);
	Iterator insertChild(Iterator parent, Node const &node);
	Iterator find(SceneID const &id);
};

template<typename SceneID>
void SceneTree<SceneID>::deleteScene(Iterator pos)
{
	Iterator begin = pos, end = pos;
	auto finalize = [](Node &node)
	{
		if(node.scene_m != nullptr) {
			node.scene_m->finalize();
			node.scene_m = nullptr;
		}
	};

	while(end.isParent()) { end.goLastChild(); }
	std::for_each(begin, ++end, finalize);
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::end()const
{
	return sceneTree_m.end();
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::begin()const
{
	return sceneTree_m.begin();
}

template<typename SceneID>
typename void SceneTree<SceneID>::clear()
{
	deleteScene(begin());
	sceneTree_m.clear();
}

template<typename SceneID>
typename void SceneTree<SceneID>::erase(Iterator pos)
{
	deleteScene(pos);
	sceneTree_m.erase(pos);
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::find(SceneID const &id)
{
	return sceneTree_m.find({ id, nullptr });
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::insertRoot(Node const &node)
{
	return sceneTree_m.insert_root(node);
}

template<typename SceneID>
typename SceneTree<SceneID>::Iterator SceneTree<SceneID>::insertChild(
	Iterator parent, Node const &node)
{
	return sceneTree_m.insert_child(parent, node);
}

}
}