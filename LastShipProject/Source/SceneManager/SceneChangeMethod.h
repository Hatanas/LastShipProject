#pragma once

#include "BaseSceneChangeMethod.h"

namespace projectj {
namespace scenemanager {

template<typename SceneID>
class BaseScene;
template<typename SceneID>
class SceneTree;
template<typename SceneID>
class SceneNode;
template<typename SceneID>
class SceneFactory;

}
}

namespace projectj {
namespace scenemanager {

template<typename SceneID>
class KeepScene : public BaseSceneChangeMethod<SceneID>
{
private:
	typedef SceneID ID_t;
	typedef BaseSceneChangeMethod<SceneID> Base_t;
	typedef typename Tree<SceneNode<SceneID>>::preorder_iterator Iterator_t;
	typedef SceneFactory<SceneID> Factory_t;
	typedef SceneTree<SceneID> Tree_t;
	typedef SceneNode<SceneID> Node_t;
	typedef std::shared_ptr<BaseScene<SceneID>> SharedScene_t;
public:
	KeepScene(ID_t const &id) :Base_t(id) {}
public:
	Iterator_t changeScene(
		Factory_t const &factory, Tree_t &tree, Iterator_t &current) const
	{
		return current;
	}
};


template<typename SceneID>
class ClearScene : public BaseSceneChangeMethod<SceneID>
{
private:
	typedef SceneID ID_t;
	typedef BaseSceneChangeMethod<SceneID> Base_t;
	typedef typename Tree<SceneNode<SceneID>>::preorder_iterator Iterator_t;
	typedef SceneFactory<SceneID> Factory_t;
	typedef SceneTree<SceneID> Tree_t;
	typedef SceneNode<SceneID> Node_t;
	typedef std::shared_ptr<BaseScene<SceneID>> SharedScene_t;
public:
	ClearScene(SceneID const &id) :Base_t(id)
	{}
public:
	Iterator_t changeScene(
		Factory_t const &factory, Tree_t &tree, Iterator_t &current) const
	{
		tree.clear();
		return tree.end();
	}
};


template<typename SceneID>
class PopScene : public BaseSceneChangeMethod<SceneID>
{
private:
	typedef SceneID ID_t;
	typedef BaseSceneChangeMethod<SceneID> Base_t;
	typedef typename Tree<SceneNode<SceneID>>::preorder_iterator Iterator_t;
	typedef SceneFactory<SceneID> Factory_t;
	typedef SceneTree<SceneID> Tree_t;
	typedef SceneNode<SceneID> Node_t;
	typedef std::shared_ptr<BaseScene<SceneID>> SharedScene_t;
public:
	PopScene(SceneID const &id) :Base_t(id) {}
public:
	Iterator_t changeScene(
		Factory_t const &factory, Tree_t &tree, Iterator_t &current) const
	{
		if(current == tree.end()) { return tree.end(); }
		if(current.isRoot()) { return tree.end(); }

		auto target = current, parent = current;

		parent.goParent();
		tree.erase(target);

		return parent;
	}
};


template<typename SceneID>
class ResetScene : public BaseSceneChangeMethod<SceneID>
{
private:
	typedef SceneID ID_t;
	typedef BaseSceneChangeMethod<SceneID> Base_t;
	typedef typename Tree<SceneNode<SceneID>>::preorder_iterator Iterator_t;
	typedef SceneFactory<SceneID> Factory_t;
	typedef SceneTree<SceneID> Tree_t;
	typedef SceneNode<SceneID> Node_t;
	typedef std::shared_ptr<BaseScene<SceneID>> SharedScene_t;
public:
	ResetScene(SceneID const &id) :Base_t(id) {}
public:
	Iterator_t changeScene(
		Factory_t const &factory, Tree_t &tree, Iterator_t &current) const
	{
		SharedScene_t scene = factory.getScene(nextID_m);

		tree.clear();

		if(scene == nullptr) { return tree.end(); }
		scene->initialize();
		return tree.setRoot({ nextID_m, scene });
	}
};


template<typename SceneID>
class PushScene : public BaseSceneChangeMethod<SceneID>
{
private:
	typedef SceneID ID_t;
	typedef BaseSceneChangeMethod<SceneID> Base_t;
	typedef typename Tree<SceneNode<SceneID>>::preorder_iterator Iterator_t;
	typedef SceneFactory<SceneID> Factory_t;
	typedef SceneTree<SceneID> Tree_t;
	typedef SceneNode<SceneID> Node_t;
	typedef std::shared_ptr<BaseScene<SceneID>> SharedScene_t;
public:
	PushScene(SceneID const &id) :Base_t(id) {}
public:
	Iterator_t changeScene(
		Factory_t const &factory, Tree_t &tree, Iterator_t &current) const
	{
		SharedScene_t scene = factory.getScene(nextID_m);
		if(scene == nullptr) { return tree.end(); }

		Iterator_t child = tree.insertChild(current, { nextID_m, scene });
		if(child == tree.end()) { return tree.end(); }

		scene->initialize();

		return child;
	}
};


template<typename SceneID>
class JumpScene : public BaseSceneChangeMethod<SceneID>
{
private:
	typedef SceneID ID_t;
	typedef BaseSceneChangeMethod<SceneID> Base_t;
	typedef typename Tree<SceneNode<SceneID>>::preorder_iterator Iterator_t;
	typedef SceneFactory<SceneID> Factory_t;
	typedef SceneTree<SceneID> Tree_t;
	typedef SceneNode<SceneID> Node_t;
	typedef std::shared_ptr<BaseScene<SceneID>> SharedScene_t;
public:
	JumpScene(SceneID const &id) :Base_t(id) {}
public:
	Iterator_t changeScene(
		Factory_t const &factory, Tree_t &tree, Iterator_t &current) const
	{
		Iterator_t iterator = tree.find(nextID_m);

		if(iterator == tree.end()) {
			iterator = PushScene<ID_t>(nextID_m).changeScene(
				factory, tree, current);
		}

		return iterator;
	}
};


template<typename SceneID>
class ParentScene : public BaseSceneChangeMethod<SceneID>
{
private:
	typedef SceneID ID_t;
	typedef BaseSceneChangeMethod<SceneID> Base_t;
	typedef typename Tree<SceneNode<SceneID>>::preorder_iterator Iterator_t;
	typedef SceneFactory<SceneID> Factory_t;
	typedef SceneTree<SceneID> Tree_t;
	typedef SceneNode<SceneID> Node_t;
	typedef std::shared_ptr<BaseScene<SceneID>> SharedScene_t;
public:
	ParentScene(SceneID const &id) :Base_t(id) {}
public:
	Iterator_t changeScene(
		Factory_t const &factory, Tree_t &tree, Iterator_t &current) const
	{
		if(current.isRoot() || current == tree.end()) { return tree.end(); }
		Iterator_t parent = current;
		parent.goParent();

		return parent;
	}
};


template<typename SceneID>
class ChildScene : public BaseSceneChangeMethod<SceneID>
{
private:
	typedef SceneID ID_t;
	typedef BaseSceneChangeMethod<SceneID> Base_t;
	typedef typename Tree<SceneNode<SceneID>>::preorder_iterator Iterator_t;
	typedef SceneFactory<SceneID> Factory_t;
	typedef SceneTree<SceneID> Tree_t;
	typedef SceneNode<SceneID> Node_t;
	typedef std::shared_ptr<BaseScene<SceneID>> SharedScene_t;
public:
	ChildScene(SceneID const &id) :Base_t(id) {}
public:
	Iterator_t changeScene(
		Factory_t const &factory, Tree_t &tree, Iterator_t &current) const
	{
		if(current.isLeaf()) { return tree.end(); }

		Iterator_t firstChild = current;
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

}
}
