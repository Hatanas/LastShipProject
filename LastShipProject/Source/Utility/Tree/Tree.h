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
	TreeNode<T> *head_m;
	TreeNode<T> *tail_m;
	std::map<T, TreeNode<T> *> nodeMap_m;
public:
	Tree();
	Tree(const Tree& t);
	~Tree();
	Tree& operator=(const Tree& t);
	void clear();
	bool empty() const;
	size_t size() const;
	size_t height() const;
	pre_order_iterator begin() const;
	pre_order_iterator rbegin() const;
	pre_order_iterator end() const;
	pre_order_iterator rend() const;
	pre_order_iterator insert_root(const T &key);
	pre_order_iterator insert_parent(pre_order_iterator child, const T &key);
	pre_order_iterator insert_sibling(pre_order_iterator sibling, const T &key);
	pre_order_iterator insert_child(pre_order_iterator parent, const T& key);
	pre_order_iterator find(const T& key);
	void erase(pre_order_iterator pos);
	pre_order_iterator move(
		pre_order_iterator dst, pre_order_iterator src, MoveDirection dir);
protected:
	void disconect(pre_order_iterator &src);
	void connectToNextSibling(pre_order_iterator &dst, pre_order_iterator &src);
	void connectToPrevSibling(pre_order_iterator &dst, pre_order_iterator &src);
	void connectToFirstChild(pre_order_iterator &dst, pre_order_iterator &src);
	void connectToLastChild(pre_order_iterator &dst, pre_order_iterator &src);
	void initialize();
	void finalize();
	void copy(pre_order_iterator &begin, pre_order_iterator &end);
};


template<typename T>
inline Tree<T>::Tree()
{
	initialize();
}

template<typename T>
inline Tree<T>::Tree(const Tree& t)
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
inline Tree<T>& Tree<T>::operator=(const Tree<T>& t)
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
	if (head_m->next_sibling_m != tail_m) {
		TreeNode<T>* current = head_m->next_sibling_m;
		TreeNode<T>* next;
		do {
			next = current->next_sibling_m;
			erase(pre_order_iterator(current));
			current = next;
		} while (next != tail_m);
	}
}

template<typename T>
inline bool Tree<T>::empty() const { return head_m->next_sibling_m == tail_m; }

template<typename T>
inline size_t Tree<T>::size() const { return nodeMap_m.size(); }

template<typename T>
size_t Tree<T>::height() const
{
	size_t height = 0;
	pre_order_iterator iterator = begin();

	while (iterator != end()){
		if (iterator.isLeaf() && iterator.depth() > height){
			height = iterator.depth();
		}
	}
	return height;
}

template<typename T>
inline typename PreOrderIterator<T> Tree<T>::begin() const
{
	return pre_order_iterator(head_m->next_sibling_m);
}

template<typename T>
inline PreOrderIterator<T> Tree<T>::rbegin() const { return --end(); }

template<typename T>
inline PreOrderIterator<T> Tree<T>::end() const
{
	return pre_order_iterator(tail_m);
}

template<typename T>
inline PreOrderIterator<T> Tree<T>::rend() const
{
	return pre_order_iterator(head_m);
}

template<typename T>
inline PreOrderIterator<T> Tree<T>::insert_root(const T &key)
{
	clear();
	return insert_sibling(pre_order_iterator(head_m), key);
}

template<typename T>
PreOrderIterator<T> Tree<T>::insert_parent(
	pre_order_iterator child, const T &key)
{
	if (find(key) != end()){ return end(); }
	if (empty()) {
		return insert_root(key);
	}
	else if (child == end()){ return end(); }

	// add node with key as child's parent
	TreeNode<T>* newNode = new TreeNode<T>(key);
	nodeMap_m.insert(std::make_pair(key, newNode));
	newNode->parent_m = child.myNode_m->parent_m;
	newNode->prev_sibling_m = child.myNode_m->prev_sibling_m;
	newNode->next_sibling_m = child.myNode_m->next_sibling_m;
	newNode->first_child_m = child.myNode_m;
	newNode->last_child_m = child.myNode_m;
	if (child.myNode_m->next_sibling_m != nullptr) {
		child.myNode_m->next_sibling_m->prev_sibling_m = newNode;
	}
	else{
		if (child.myNode_m->parent_m != nullptr){
			child.myNode_m->parent_m->last_child_m = newNode;
		}
	}
	if (child.myNode_m->prev_sibling_m != nullptr){
		child.myNode_m->prev_sibling_m->next_sibling_m = newNode;
	}
	else{
		if (child.myNode_m->parent_m != nullptr){
			child.myNode_m->parent_m->first_child_m = newNode;
		}
	}
	child.myNode_m->next_sibling_m = nullptr;
	child.myNode_m->prev_sibling_m = nullptr;
	child.myNode_m->parent_m = newNode;

	return pre_order_iterator(newNode);
}

template<typename T>
PreOrderIterator<T> Tree<T>::insert_sibling(
	pre_order_iterator sibling, const T &key)
{
	if (find(key) != end()){ return end(); }
	if (empty()) {
		sibling = pre_order_iterator(head_m);
	}
	else if (sibling.myNode_m->parent_m == nullptr){ return end(); }

	// add node with key after sibling
	TreeNode<T>* newNode = new TreeNode<T>(key);
	nodeMap_m.insert(std::make_pair(key, newNode));
	newNode->parent_m = sibling.myNode_m->parent_m;
	newNode->prev_sibling_m = sibling.myNode_m;
	newNode->next_sibling_m = sibling.myNode_m->next_sibling_m;
	if (sibling.myNode_m->next_sibling_m != nullptr) {
		sibling.myNode_m->next_sibling_m->prev_sibling_m = newNode;
	}
	else{
		if (newNode->parent_m != nullptr) {
			newNode->parent_m->last_child_m = newNode;
		}
	}
	sibling.myNode_m->next_sibling_m = newNode;

	return pre_order_iterator(newNode);
}

template<typename T>
PreOrderIterator<T> Tree<T>::insert_child(
	pre_order_iterator parent, const T& key)
{
	if (find(key) != end()){ return end(); }
	if (empty()) {
		return insert_root(key);
	}
	else if (parent == end()){ return end(); }

	TreeNode<T>* newNode = new TreeNode<T>(key);
	nodeMap_m.insert(std::make_pair(key, newNode));
	newNode->parent_m = parent.myNode_m;
	if (parent.myNode_m->last_child_m != nullptr) {
		parent.myNode_m->last_child_m->next_sibling_m = newNode;
		newNode->prev_sibling_m = parent.myNode_m->last_child_m;
	}
	else {
		parent.myNode_m->first_child_m = newNode;
	}
	parent.myNode_m->last_child_m = newNode;

	return pre_order_iterator(newNode);
}

template<typename T>
inline PreOrderIterator<T> Tree<T>::find(const T& key)
{
	typename std::map<T, TreeNode<T>*>::iterator itr = nodeMap_m.find(key);
	if (itr != nodeMap_m.end()) {
		return pre_order_iterator(itr->second);
	}
	else{
		return end();
	}
}

template<typename T>
void Tree<T>::erase(pre_order_iterator pos)
{
	if (pos.myNode_m == head_m) { return; }
	if (pos.myNode_m == tail_m) { return; }

	// erase subtree of pos
	while (pos.myNode_m->first_child_m) {
		erase(pre_order_iterator(pos.myNode_m->first_child_m));
	}

	TreeNode<T>* deleteNode = pos.myNode_m;
	if (!deleteNode->prev_sibling_m) {
		deleteNode->parent_m->first_child_m = deleteNode->next_sibling_m;
	}
	else {
		deleteNode->prev_sibling_m->next_sibling_m = deleteNode->next_sibling_m;
	}
	if (!deleteNode->next_sibling_m) {
		deleteNode->parent_m->last_child_m = deleteNode->prev_sibling_m;
	}
	else {
		deleteNode->next_sibling_m->prev_sibling_m = deleteNode->prev_sibling_m;
	}
	if (deleteNode->parent_m) {
		if (deleteNode->parent_m->first_child_m == deleteNode &&
			deleteNode->parent_m->last_child_m == deleteNode) {
			deleteNode->parent_m->first_child_m = nullptr;
			deleteNode->parent_m->last_child_m = nullptr;
		}
	}
	if (deleteNode->key_m) {
		nodeMap_m.erase(*deleteNode->key_m);
	}
	delete deleteNode;
}

template<typename T>
PreOrderIterator<T> Tree<T>::move(
	pre_order_iterator dst, pre_order_iterator src, MoveDirection dir)
{
	if (dst == src) { return end(); }
	if (dst == end() || src == end()){ return end(); }
	pre_order_iterator tmp = dst;
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
void Tree<T>::disconect(pre_order_iterator &src){
	if (src.myNode_m->prev_sibling_m) {
		src.myNode_m->prev_sibling_m->next_sibling_m = src.myNode_m->next_sibling_m;
	}
	else {
		if (src.myNode_m->parent_m) {
			src.myNode_m->parent_m->first_child_m = src.myNode_m->next_sibling_m;
		}
	}
	if (src.myNode_m->next_sibling_m) {
		src.myNode_m->next_sibling_m->prev_sibling_m = src.myNode_m->prev_sibling_m;
	}
	else {
		if (src.myNode_m->parent_m) {
			src.myNode_m->parent_m->last_child_m = src.myNode_m->prev_sibling_m;
		}
	}
}

template<typename T>
void Tree<T>::connectToNextSibling(
	pre_order_iterator &dst, pre_order_iterator &src)
{
	src.myNode_m->parent_m = dst.myNode_m->parent_m;
	if (dst.myNode_m->next_sibling_m) {
		dst.myNode_m->next_sibling_m->prev_sibling_m = src.myNode_m;
	}
	else {
		src.myNode_m->parent_m->last_child_m = src.myNode_m;
	}
	src.myNode_m->next_sibling_m = dst.myNode_m->next_sibling_m;
	dst.myNode_m->next_sibling_m = src.myNode_m;
	src.myNode_m->prev_sibling_m = dst.myNode_m;
}

template<typename T>
void Tree<T>::connectToPrevSibling(
	pre_order_iterator &dst, pre_order_iterator &src)
{
	src.myNode_m->parent_m = dst.myNode_m->parent_m;
	if (dst.myNode_m->prev_sibling_m != nullptr) {
		dst.myNode_m->prev_sibling_m->next_sibling_m = src.myNode_m;
	}
	else {
		dst.myNode_m->parent_m->first_child_m = src.myNode_m;
	}
	src.myNode_m->prev_sibling_m = dst.myNode_m->prev_sibling_m;
	src.myNode_m->next_sibling_m = dst.myNode_m;
	dst.myNode_m->prev_sibling_m = src.myNode_m;
}

template<typename T>
void Tree<T>::connectToFirstChild(
	pre_order_iterator &dst, pre_order_iterator &src)
{
	if (dst.myNode_m->first_child_m) {
		dst.myNode_m->first_child_m->prev_sibling_m = src.myNode_m;
	}
	else {
		dst.myNode_m->last_child_m = src.myNode_m;
	}
	src.myNode_m->parent_m = dst.myNode_m;
	src.myNode_m->next_sibling_m = dst.myNode_m->first_child_m;
	dst.myNode_m->first_child_m = src.myNode_m;
	src.myNode_m->prev_sibling_m = nullptr;
}

template<typename T>
void Tree<T>::connectToLastChild(
	pre_order_iterator &dst, pre_order_iterator &src)
{
	if (!dst.myNode_m->first_child_m) {
		dst.myNode_m->first_child_m = src.myNode_m;
	}
	if (dst.myNode_m->last_child_m) {
		dst.myNode_m->last_child_m->next_sibling_m = src.myNode_m;
	}
	src.myNode_m->parent_m = dst.myNode_m;
	src.myNode_m->prev_sibling_m = dst.myNode_m->last_child_m;
	dst.myNode_m->last_child_m = src.myNode_m;
	src.myNode_m->next_sibling_m = nullptr;
}

template<typename T>
inline void Tree<T>::initialize()
{
	head_m = new TreeNode<T>();
	tail_m = new TreeNode<T>();

	head_m->next_sibling_m = tail_m;
	head_m->prev_sibling_m = head_m;
	tail_m->prev_sibling_m = head_m;
	tail_m->next_sibling_m = tail_m;
}

template<typename T>
inline void Tree<T>::finalize()
{
	clear();
	delete head_m; head_m = nullptr;
	delete tail_m; tail_m = nullptr;
}

template<typename T>
void Tree<T>::copy(
	pre_order_iterator &begin, pre_order_iterator &end)
{
	for (pre_order_iterator itr = begin; itr != end; ++itr) {
		TreeNode<T>* current = itr.myNode_m;
		if (current->parent_m != nullptr) {
			S key = *current->parent_m->key_m;
			insert_child(find(key), T(*current->key_m));
		}
		else {
			insert_child(this->begin(), T(*current->key_m));
		}
	}
}
