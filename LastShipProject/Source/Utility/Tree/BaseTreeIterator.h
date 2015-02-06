#pragma once

#include <iterator>
#include <cassert>
#include "TreeNode.h"

template<typename T>
class Tree;

template<typename T>
class BaseTreeIterator :
	public std::iterator<std::forward_iterator_tag, T>
{
protected:
	friend class Tree<T>;
	TreeNode<T>* myNode_m;
	BaseTreeIterator() : myNode_m(nullptr) {}
public:
	explicit BaseTreeIterator(TreeNode<T>* node) : myNode_m(node){}

	size_t depth() const;
	bool isNull() const;
	bool isRoot() const;
	bool isLeaf() const;
	bool isFirst() const;
	bool isLast() const;
	bool isParent() const;
	void goParent();
	void goNextSibling();
	void goPrevSibling();
	void goFirstChild();
	void goLastChild();
	T& operator*() const;
	T* operator->() const;
	bool operator==(const BaseTreeIterator iterator) const;
	bool operator!=(const BaseTreeIterator iterator) const;
	operator bool() const;
	bool operator!() const;
};

template<typename T>
size_t BaseTreeIterator<T>::depth() const
{
	size_t depth = 0;
	if (myNode_m == nullptr){ return depth; }

	if (myNode_m->parent_m != nullptr){
		TreeNode<T>* currrent = myNode_m;
		while (currrent->parent_m != nullptr) {
			++depth;
			currrent = currrent->parent_m;
		}
	}

	return depth;
}

template<typename T>
inline bool BaseTreeIterator<T>::isNull() const{ return myNode_m == nullptr; }

template<typename T>
inline bool BaseTreeIterator<T>::isRoot() const
{
	assert(!isNull());
	return myNode_m->parent_m == nullptr &&
		myNode_m->nextSibling_m != nullptr &&
		myNode_m->nextSibling_m != myNode_m &&
		myNode_m->prevSibling_m != nullptr &&
		myNode_m->prevSibling_m != myNode_m;
}

template<typename T>
inline bool BaseTreeIterator<T>::isLeaf() const
{
	assert(!isNull());
	return (isRoot() || myNode_m->parent_m != nullptr) &&
		myNode_m->firstChild_m == nullptr &&
		myNode_m->lastChild_m == nullptr;
}

template<typename T>
inline bool BaseTreeIterator<T>::isFirst() const
{
	assert(!isNull());
	return isRoot() ||
		(myNode_m->parent_m != nullptr &&
		myNode_m->prevSibling_m == nullptr);
}

template<typename T>
inline bool BaseTreeIterator<T>::isLast() const
{
	assert(!isNull());
	return isRoot() ||
		(myNode_m->parent_m != nullptr &&
		myNode_m->nextSibling_m == nullptr);
}

template<typename T>
inline bool BaseTreeIterator<T>::isParent() const
{
	assert(!isNull());
	return myNode_m->firstChild_m != nullptr &&
		myNode_m->lastChild_m != nullptr;
}

template<typename T>
inline void BaseTreeIterator<T>::goParent()
{
	assert(!isNull());
	assert(myNode_m->parent_m != nullptr);
	if (myNode_m->parent_m == nullptr){ return; }

	myNode_m = myNode_m->parent_m;
}

template<typename T>
inline void BaseTreeIterator<T>::goNextSibling()
{
	assert(!isNull());
	if (myNode_m->nextSibling_m == nullptr){ return; }

	myNode_m = myNode_m->nextSibling_m;
}

template<typename T>
inline void BaseTreeIterator<T>::goPrevSibling()
{
	assert(!isNull());
	if (myNode_m->prevSibling_m == nullptr){ return; }

	myNode_m = myNode_m->prevSibling_m;
}

template<typename T>
inline void BaseTreeIterator<T>::goFirstChild()
{
	assert(!isNull());
	if (myNode_m->firstChild_m == nullptr){ return; }

	myNode_m = myNode_m->firstChild_m;
}

template<typename T>
inline void BaseTreeIterator<T>::goLastChild()
{
	assert(!isNull());
	if (myNode_m->lastChild_m == nullptr){ return; }

	myNode_m = myNode_m->lastChild_m;
}

template<typename T>
inline T& BaseTreeIterator<T>::operator*() const
{ 
	assert(!isNull());
	return *myNode_m->key_m;
}

template<typename T>
inline T* BaseTreeIterator<T>::operator->() const
{
	assert(!isNull());
	return &(operator*());
}

template<typename T>
inline bool BaseTreeIterator<T>::operator==(
	const BaseTreeIterator iterator) const
{
	if(isNull() || iterator.isNull()) { return false; }
	return myNode_m->key_m == iterator.myNode_m->key_m;
}

template<typename T>
inline bool BaseTreeIterator<T>::operator!=(
	const BaseTreeIterator iterator) const
{
	if(isNull() || iterator.isNull()) { return false; }
	return !operator==(iterator);
}

template<typename T>
inline BaseTreeIterator<T>::operator bool() const
{
	return !isNull();
}

template<typename T>
inline bool BaseTreeIterator<T>::operator!() const
{
	return !operator bool();
}



