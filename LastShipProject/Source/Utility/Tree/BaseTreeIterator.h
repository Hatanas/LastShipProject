#pragma once

#include <iterator>
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
	bool goParent();
	bool goNextSibling();
	bool goPrevSibling();
	bool goFirstChild();
	bool goLastChild();
	T& operator*() const;
	T* operator->() const;
	bool operator==(const BaseTreeIterator iterator) const;
	bool operator!=(const BaseTreeIterator iterator) const;
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
	if (isNull()){ return false; }
	return myNode_m->parent_m == nullptr &&
		myNode_m->next_sibling_m != nullptr &&
		myNode_m->next_sibling_m != myNode_m &&
		myNode_m->prev_sibling_m != nullptr &&
		myNode_m->prev_sibling_m != myNode_m;
}

template<typename T>
inline bool BaseTreeIterator<T>::isLeaf() const
{
	if (isNull()){ return false; }
	return (isRoot() || myNode_m->parent_m != nullptr) &&
		myNode_m->first_child_m == nullptr &&
		myNode_m->last_child_m == nullptr;
}

template<typename T>
inline bool BaseTreeIterator<T>::isFirst() const
{
	if (isNull()){ return false; }
	return isRoot() ||
		(myNode_m->parent_m != nullptr &&
		myNode_m->prev_sibling_m == nullptr);
}

template<typename T>
inline bool BaseTreeIterator<T>::isLast() const
{
	if (isNull()){ return false; }
	return isRoot() ||
		(myNode_m->parent_m != nullptr &&
		myNode_m->next_sibling_m == nullptr);
}

template<typename T>
inline bool BaseTreeIterator<T>::isParent() const{ return !isLeaf(); }

template<typename T>
inline bool BaseTreeIterator<T>::goParent()
{
	if (isNull()){ return false; }
	if (myNode_m->parent_m == nullptr){ return false; }
	myNode_m = myNode_m->parent_m;
	return true;
}

template<typename T>
inline bool BaseTreeIterator<T>::goNextSibling()
{
	if (isNull()){ return false; }
	if (myNode_m->next_sibling_m == nullptr){ return false; }
	myNode_m = myNode_m->next_sibling_m;
	return true;
}

template<typename T>
inline bool BaseTreeIterator<T>::goPrevSibling()
{
	if (isNull()){ return false; }
	if (myNode_m->prev_sibling_m == nullptr){ return false; }
	myNode_m = myNode_m->prev_sibling_m;
	return true;
}

template<typename T>
inline bool BaseTreeIterator<T>::goFirstChild()
{
	if (isNull()){ return false; }
	if (myNode_m->first_child_m == nullptr){ return false; }
	myNode_m = myNode_m->first_child_m;
	return true;
}

template<typename T>
inline bool BaseTreeIterator<T>::goLastChild()
{
	if (isNull()){ return false; }
	if (myNode_m->last_child_m == nullptr){ return false; }
	myNode_m = myNode_m->last_child_m;
	return true;
}

template<typename T>
inline T& BaseTreeIterator<T>::operator*() const { return *myNode_m->key_m; }

template<typename T>
inline T* BaseTreeIterator<T>::operator->() const { return &(operator*()); }

template<typename T>
inline bool BaseTreeIterator<T>::operator==(
	const BaseTreeIterator iterator) const
{
	if (isNull() || iterator.isNull()){ return false; }
	return myNode_m->key_m == iterator.myNode_m->key_m;
}

template<typename T>
inline bool BaseTreeIterator<T>::operator!=(
	const BaseTreeIterator iterator) const
{
	return !operator==(iterator);
}
