#pragma once

#include "SceneFactory.h"
#include "SceneTree.h"
#include "BaseScene.h"
#include <memory>

namespace projectj {
namespace scenemanager {

template<typename SceneID>
class BaseScene;
template<typename SceneID>
class SceneTree;
template<typename SceneID>
class SceneFactory;

template<typename SceneID>
class BaseSceneChangeMethod
{
protected:
	typedef BaseScene<SceneID> Scene;
	typedef SceneFactory<SceneID> Factory;
	typedef SceneTree<SceneID> Tree;
	typedef typename Tree::SharedScene SharedScene;
	typedef typename Tree::Iterator Iterator;

	SceneID nextID_m;
public:
	BaseSceneChangeMethod(SceneID const &id) :nextID_m(id) {}
public:
	virtual Iterator changeScene(
		Factory const &factory, Tree &tree, Iterator const &current) const
	{
		return tree.end();
	}
};

template<typename SceneID>
class KeepScene : public BaseSceneChangeMethod < SceneID >
{
public:
	KeepScene(SceneID const &id)
		:BaseSceneChangeMethod<SceneID>(id) {}
public:
	virtual Iterator changeScene(
		Factory const &factory, Tree &tree, Iterator const &current) const
	{
		return current;
	}
};

template<typename SceneID>
class ClearScene : public BaseSceneChangeMethod < SceneID >
{
public:
	ClearScene(SceneID const &id)
		:BaseSceneChangeMethod<SceneID>(id) {}
public:
	Iterator changeScene(
		Factory const &factory, Tree &tree, Iterator const &current) const
	{
		tree.clear();
		return tree.end();
	}
};

template<typename SceneID>
class PopScene : public BaseSceneChangeMethod < SceneID >
{
public:
	PopScene(SceneID const &id)
		:BaseSceneChangeMethod<SceneID>(id) {}
public:
	Iterator changeScene(
		Factory const &factory, Tree &tree, Iterator const &current) const
	{
		if(current == tree.end()) { return tree.end(); }
		if(current.isRoot()) { return tree.end(); }

		Iterator target = current, parent = current;

		parent.goParent();
		tree.erase(target);

		return parent;
	}
};

template<typename SceneID>
class ResetScene : public BaseSceneChangeMethod < SceneID >
{
public:
	ResetScene(SceneID const &id)
		:BaseSceneChangeMethod<SceneID>(id) {}
public:
	Iterator changeScene(
		Factory const &factory, Tree &tree, Iterator const &current) const
	{
		SharedScene scene = factory.getScene(nextID_m);
		tree.clear();
		if(scene == nullptr) { return tree.end(); }
		scene->initialize();

		return tree.insertRoot({ nextID_m, scene });
	}
};

template<typename SceneID>
class PushScene : public BaseSceneChangeMethod < SceneID >
{
public:
	PushScene(SceneID const &id)
		:BaseSceneChangeMethod<SceneID>(id) {}
public:
	Iterator changeScene(
		Factory const &factory, Tree &tree, Iterator const &current) const
	{
		SharedScene scene = factory.getScene(nextID_m);
		if(scene == nullptr) { return tree.end(); }

		Iterator child = tree.insertChild(current, { nextID_m, scene });
		if(child == tree.end()) { return tree.end(); }

		scene->initialize();

		return child;
	}
};

template<typename SceneID>
class JumpScene : public BaseSceneChangeMethod < SceneID >
{
public:
	JumpScene(SceneID const &id)
		:BaseSceneChangeMethod<SceneID>(id) {}
public:
	Iterator changeScene(
		Factory const &factory, Tree &tree, Iterator const &current) const
	{
		Iterator iterator = tree.find(nextID_m);

		if(iterator == tree.end()) {
			iterator = PushScene<SceneID>(nextID_m).changeScene(
				factory, tree, current);
		}

		return iterator;
	}
};

template<typename SceneID>
class ParentScene : public BaseSceneChangeMethod < SceneID >
{
public:
	ParentScene(SceneID const &id)
		:BaseSceneChangeMethod<SceneID>(id) {}
public:
	Iterator changeScene(
		Factory const &factory, Tree &tree, Iterator const &current) const
	{
		if(current.isRoot() || current == tree.end()) { return tree.end(); }
		Iterator parent = current;
		parent.goParent();

		return parent;
	}
};

template<typename SceneID>
class ChildScene : public BaseSceneChangeMethod < SceneID >
{
public:
	ChildScene(SceneID const &id)
		:BaseSceneChangeMethod<SceneID>(id) {}
public:
	Iterator changeScene(
		Factory const &factory, Tree &tree, Iterator const &current) const
	{
		if(current.isLeaf()) { return tree.end(); }

		Iterator firstChild = current;
		firstChild.goFirstChild();

		while(true) {
			if(firstChild->id_m == nextID_m) { break; }
			else {
				if(firstChild.isLast()) { return tree.end(); }
				firstChild.goNextSibling();
			}
		}

		return firstChild;
	}
};


template<typename SceneID>
class SceneChangeMethodFactory
{
public:
	typedef std::unique_ptr<BaseSceneChangeMethod<SceneID>> SceneChangeMethod;

	template<class Changer>
	static SceneChangeMethod get(SceneID const&nextID)
	{
		return std::make_unique<Changer>(nextID);
	}
};

}
}