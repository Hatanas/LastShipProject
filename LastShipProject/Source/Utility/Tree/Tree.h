#pragma once

#include <map>
#include <algorithm>
#include "PreOrderIterator.h"

template<typename T>
class Tree
{
public:	
	enum MoveDirection
	{
		TO_PREV_SIBLING,
		TO_NEXT_SIBLING,
		TO_FIRST_CHILD,
		TO_LAST_CHILD
	};
	typedef PreOrderIterator<T> pre_order_iterator;
private:
	typedef pre_order_iterator iterator;
private:
	TreeNode<T> *head_m;
	TreeNode<T> *tail_m;
	std::map<T, TreeNode<T> *> nodeMap_m;
public:
	Tree();
	Tree(Tree const &t);
	~Tree();
	Tree<T>& operator=(Tree<T> const &t);
public:
	void clear();
	bool empty() const;
	size_t size() const;
	size_t height() const;
	iterator begin() const;
	iterator rbegin() const;
	iterator end() const;
	iterator rend() const;
	iterator insert_root(T const &key);
	iterator insert_parent(iterator child, T const &key);
	iterator insert_sibling(iterator sibling, T const &key);
	iterator insert_child(iterator parent, T const &key);
	iterator find(T const &key);
	void erase(iterator pos);
	iterator move(
		iterator dst, iterator src, MoveDirection dir);
protected:
	void disconect(iterator &src);
	void connectToNextSibling(iterator &dst, iterator &src);
	void connectToPrevSibling(iterator &dst, iterator &src);
	void connectToFirstChild(iterator &dst, iterator &src);
	void connectToLastChild(iterator &dst, iterator &src);
	void initialize();
	void finalize();
	void copy(iterator const &begin, iterator const &end);
};


template<typename T>
inline Tree<T>::Tree()
{
	initialize();
}

template<typename T>
inline Tree<T>::Tree(Tree const &t)
{
	initialize();
	copy(t.begin(), t.end());
}

template<typename T>
inline Tree<T>::~Tree()
{
	finalize();
}

template<typename T>
inline Tree<T>& Tree<T>::operator=(Tree<T> const &t)
{
	if (this != &t) {
		this->~Tree();
		new (this) Tree(t);
	}
	return *this;
}

template<typename T>
void Tree<T>::clear()
{
	if (head_m->nextSibling_m != tail_m) {
		TreeNode<T> *current = head_m->nextSibling_m;
		TreeNode<T> *next;
		do {
			next = current->nextSibling_m;
			erase(iterator(current));
			current = next;
		} while (next != tail_m);
	}
}

template<typename T>
inline bool Tree<T>::empty() const{ return nodeMap_m.empty(); }

template<typename T>
inline size_t Tree<T>::size() const { return nodeMap_m.size(); }

template<typename T>
size_t Tree<T>::height() const
{
	size_t height = 0;
	
	for (iterator itr = begin(); itr != end(); ++itr){
		if (itr.isLeaf() && itr.depth() > height){
			height = itr.depth();
		}
	}
	return height;
}

template<typename T>
inline typename PreOrderIterator<T> Tree<T>::begin() const
{
	return iterator(head_m->nextSibling_m);
}

template<typename T>
inline PreOrderIterator<T> Tree<T>::rbegin() const { return --end(); }

template<typename T>
inline PreOrderIterator<T> Tree<T>::end() const{ return iterator(tail_m); }

template<typename T>
inline PreOrderIterator<T> Tree<T>::rend() const{ return iterator(head_m); }

template<typename T>
inline PreOrderIterator<T> Tree<T>::insert_root(T const &key)
{
	clear();
	return insert_sibling(iterator(head_m), key);
}

template<typename T>
PreOrderIterator<T> Tree<T>::insert_parent(
	iterator child, T const &key)
{
	if (find(key) != end()){ return end(); }
	if (empty()) {
		return insert_root(key);
	}
	else if (child == end()){ return end(); }

	TreeNode<T>* newNode = new TreeNode<T>(key);
	nodeMap_m.insert(std::make_pair(key, newNode));
	newNode->parent_m = child.myNode_m->parent_m;
	newNode->prevSibling_m = child.myNode_m->prevSibling_m;
	newNode->nextSibling_m = child.myNode_m->nextSibling_m;
	newNode->firstChild_m = child.myNode_m;
	newNode->lastChild_m = child.myNode_m;
	if (child.myNode_m->nextSibling_m != nullptr) {
		child.myNode_m->nextSibling_m->prevSibling_m = newNode;
	}
	else{
		if (child.myNode_m->parent_m != nullptr){
			child.myNode_m->parent_m->lastChild_m = newNode;
		}
	}
	if (child.myNode_m->prevSibling_m != nullptr){
		child.myNode_m->prevSibling_m->nextSibling_m = newNode;
	}
	else{
		if (child.myNode_m->parent_m != nullptr){
			child.myNode_m->parent_m->firstChild_m = newNode;
		}
	}
	child.myNode_m->nextSibling_m = nullptr;
	child.myNode_m->prevSibling_m = nullptr;
	child.myNode_m->parent_m = newNode;

	return iterator(newNode);
}

template<typename T>
PreOrderIterator<T> Tree<T>::insert_sibling(
	iterator sibling, T const &key)
{
	if (find(key) != end()){ return end(); }
	if (empty()) {
		sibling = iterator(head_m);
	}
	else if (sibling.myNode_m->parent_m == nullptr){ return end(); }

	TreeNode<T>* newNode = new TreeNode<T>(key);
	nodeMap_m.insert(std::make_pair(key, newNode));
	newNode->parent_m = sibling.myNode_m->parent_m;
	newNode->prevSibling_m = sibling.myNode_m;
	newNode->nextSibling_m = sibling.myNode_m->nextSibling_m;
	if (sibling.myNode_m->nextSibling_m != nullptr) {
		sibling.myNode_m->nextSibling_m->prevSibling_m = newNode;
	}
	else{
		if (newNode->parent_m != nullptr) {
			newNode->parent_m->lastChild_m = newNode;
		}
	}
	sibling.myNode_m->nextSibling_m = newNode;

	return iterator(newNode);
}

template<typename T>
PreOrderIterator<T> Tree<T>::insert_child(
	iterator parent, const T& key)
{
	if (find(key) != end()){ return end(); }
	if (empty()) {
		return insert_root(key);
	}
	else if (parent == end()){ return end(); }

	TreeNode<T>* newNode = new TreeNode<T>(key);
	nodeMap_m.insert(std::make_pair(key, newNode));
	newNode->parent_m = parent.myNode_m;
	if (parent.myNode_m->lastChild_m != nullptr) {
		parent.myNode_m->lastChild_m->nextSibling_m = newNode;
		newNode->prevSibling_m = parent.myNode_m->lastChild_m;
	}
	else {
		parent.myNode_m->firstChild_m = newNode;
	}
	parent.myNode_m->lastChild_m = newNode;

	return iterator(newNode);
}

template<typename T>
inline PreOrderIterator<T> Tree<T>::find(T const &key)
{
	typename std::map<T, TreeNode<T>*>::iterator itr
		= nodeMap_m.find(key);
	if (itr != nodeMap_m.end()) {
		return iterator(itr->second);
	}
	else{
		return end();
	}
}

template<typename T>
void Tree<T>::erase(iterator pos)
{
	if (pos.myNode_m == head_m) { return; }
	if (pos.myNode_m == tail_m) { return; }

	// erase subtree of pos
	 while (pos.myNode_m->firstChild_m) {
		erase(iterator(pos.myNode_m->firstChild_m));
	}

	TreeNode<T>* deleteNode = pos.myNode_m;
	if (!deleteNode->prevSibling_m) {
		deleteNode->parent_m->firstChild_m = deleteNode->nextSibling_m;
	}
	else {
		deleteNode->prevSibling_m->nextSibling_m = deleteNode->nextSibling_m;
	}
	if (!deleteNode->nextSibling_m) {
		deleteNode->parent_m->lastChild_m = deleteNode->prevSibling_m;
	}
	else {
		deleteNode->nextSibling_m->prevSibling_m = deleteNode->prevSibling_m;
	}
	if (deleteNode->parent_m) {
		if (deleteNode->parent_m->firstChild_m == deleteNode &&
			deleteNode->parent_m->lastChild_m == deleteNode) {
			deleteNode->parent_m->firstChild_m = nullptr;
			deleteNode->parent_m->lastChild_m = nullptr;
		}
	}
	if (deleteNode->key_m) {
		nodeMap_m.erase(*deleteNode->key_m);
	}
	delete deleteNode;
}

template<typename T>
PreOrderIterator<T> Tree<T>::move(
	iterator dst, iterator src, MoveDirection dir)
{
	if (dst == src) { return end(); }
	if (dst == end() || src == end()){ return end(); }
	iterator tmp = dst;
	while (tmp.myNode_m->parent_m != nullptr){
		tmp.myNode_m = tmp.myNode_m->parent_m;
		if (tmp == src){ return end(); }
	}
	switch (dir){
	case TO_NEXT_SIBLING:
		if (dst.isRoot()){ return end(); }
		disconect(src);
		connectToNextSibling(dst, src);
		break;
	case TO_PREV_SIBLING:
		if (dst.isRoot()){ return end(); }
		disconect(src);
		connectToPrevSibling(dst, src);
		break;
	case TO_FIRST_CHILD:
		disconect(src);
		connectToFirstChild(dst, src);
		break;
	case TO_LAST_CHILD:
		disconect(src);
		connectToLastChild(dst, src);
		break;
	default:
		return end();
	}

	return src;
}

template<typename T>
void Tree<T>::disconect(iterator &src){
	if (src.myNode_m->prevSibling_m) {
		src.myNode_m->prevSibling_m->nextSibling_m = src.myNode_m->nextSibling_m;
	}
	else {
		if (src.myNode_m->parent_m) {
			src.myNode_m->parent_m->firstChild_m = src.myNode_m->nextSibling_m;
		}
	}
	if (src.myNode_m->nextSibling_m) {
		src.myNode_m->nextSibling_m->prevSibling_m = src.myNode_m->prevSibling_m;
	}
	else {
		if (src.myNode_m->parent_m) {
			src.myNode_m->parent_m->lastChild_m = src.myNode_m->prevSibling_m;
		}
	}
}

template<typename T>
void Tree<T>::connectToNextSibling(iterator &dst, iterator &src)
{
	src.myNode_m->parent_m = dst.myNode_m->parent_m;
	if (dst.myNode_m->nextSibling_m) {
		dst.myNode_m->nextSibling_m->prevSibling_m = src.myNode_m;
	}
	else {
		src.myNode_m->parent_m->lastChild_m = src.myNode_m;
	}
	src.myNode_m->nextSibling_m = dst.myNode_m->nextSibling_m;
	dst.myNode_m->nextSibling_m = src.myNode_m;
	src.myNode_m->prevSibling_m = dst.myNode_m;
}

template<typename T>
void Tree<T>::connectToPrevSibling(iterator &dst, iterator &src)
{
	src.myNode_m->parent_m = dst.myNode_m->parent_m;
	if (dst.myNode_m->prevSibling_m != nullptr) {
		dst.myNode_m->prevSibling_m->nextSibling_m = src.myNode_m;
	}
	else {
		dst.myNode_m->parent_m->firstChild_m = src.myNode_m;
	}
	src.myNode_m->prevSibling_m = dst.myNode_m->prevSibling_m;
	src.myNode_m->nextSibling_m = dst.myNode_m;
	dst.myNode_m->prevSibling_m = src.myNode_m;
}

template<typename T>
void Tree<T>::connectToFirstChild(iterator &dst, iterator &src)
{
	if (dst.myNode_m->firstChild_m) {
		dst.myNode_m->firstChild_m->prevSibling_m = src.myNode_m;
	}
	else {
		dst.myNode_m->lastChild_m = src.myNode_m;
	}
	src.myNode_m->parent_m = dst.myNode_m;
	src.myNode_m->nextSibling_m = dst.myNode_m->firstChild_m;
	dst.myNode_m->firstChild_m = src.myNode_m;
	src.myNode_m->prevSibling_m = nullptr;
}

template<typename T>
void Tree<T>::connectToLastChild(iterator &dst, iterator &src)
{
	if (!dst.myNode_m->firstChild_m) {
		dst.myNode_m->firstChild_m = src.myNode_m;
	}
	if (dst.myNode_m->lastChild_m) {
		dst.myNode_m->lastChild_m->nextSibling_m = src.myNode_m;
	}
	src.myNode_m->parent_m = dst.myNode_m;
	src.myNode_m->prevSibling_m = dst.myNode_m->lastChild_m;
	dst.myNode_m->lastChild_m = src.myNode_m;
	src.myNode_m->nextSibling_m = nullptr;
}

template<typename T>
inline void Tree<T>::initialize()
{
	head_m = new TreeNode<T>();
	tail_m = new TreeNode<T>();

	head_m->nextSibling_m = tail_m;
	head_m->prevSibling_m = head_m;
	tail_m->prevSibling_m = head_m;
	tail_m->nextSibling_m = tail_m;
}

template<typename T>
inline void Tree<T>::finalize()
{
	clear();
	delete head_m; head_m = nullptr;
	delete tail_m; tail_m = nullptr;
}

template<typename T>
void Tree<T>::copy(iterator const &begin, iterator const &end)
{
	for(iterator itr = begin; itr != end; ++itr) {
		TreeNode<T>* current = itr.myNode_m;
		if (current->parent_m != nullptr) {
			T key = *current->parent_m->key_m;
			insert_child(find(key), T(*current->key_m));
		}
		else {
			insert_child(this->begin(), T(*current->key_m));
		}
	}
}

