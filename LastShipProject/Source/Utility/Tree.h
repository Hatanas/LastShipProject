#pragma once

#include <map>
#include <algorithm>
#include <iterator>

template<typename T>
class Tree;

template<typename T>
class TreeNode
{
public:
	TreeNode<T>* parent_m;
	TreeNode<T>* first_child_m;
	TreeNode<T>* last_child_m;
	TreeNode<T>* prev_sibling_m;
	TreeNode<T>* next_sibling_m;
	T* key_m;
public:
	TreeNode()
	{
		parent_m = first_child_m = last_child_m = prev_sibling_m = first_child_m = nullptr;
		key_m = new T();
	}
	TreeNode(const T& key)
	{
		parent_m = first_child_m = last_child_m = prev_sibling_m = first_child_m = nullptr;
		key_m = new T(key);
	}
	~TreeNode()
	{
		delete key_m;
	}	
};

template<typename T>
class BaseIterator :
	public std::iterator<std::forward_iterator_tag, T>
{
protected:
	friend class Tree<T>;
	TreeNode<T>* myNode_m;
	BaseIterator() : myNode_m(nullptr) {}
public:
	explicit BaseIterator(TreeNode<T>* node) : myNode_m(node){}

	size_t depth()const
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
	bool isNull()const{ return myNode_m == nullptr; }
	bool isRoot()const
	{
		if (isNull()){ return false; }
		return myNode_m->parent_m == nullptr &&
			myNode_m->next_sibling_m != nullptr &&
			myNode_m->next_sibling_m != myNode_m &&
			myNode_m->prev_sibling_m != nullptr &&
			myNode_m->prev_sibling_m != myNode_m;
	}
	bool isLeaf()const
	{
		if (isNull()){ return false; }
		return (isRoot() || myNode_m->parent_m != nullptr) &&
			myNode_m->first_child_m == nullptr &&
			myNode_m->last_child_m == nullptr;
	}
	bool isFirst()const
	{
		if (isNull()){ return false; }
		return isRoot() ||
			(myNode_m->parent_m != nullptr &&
			myNode_m->prev_sibling_m == nullptr);
	}
	bool isLast()const
	{
		if (isNull()){ return false; }
		return isRoot() ||
			(myNode_m->parent_m != nullptr &&
			myNode_m->next_sibling_m == nullptr);
	}
	bool isParent()const
	{
		return !isLeaf();
	}
	bool goParent()
	{
		if (isNull()){ return false; }
		if (myNode_m->parent_m == nullptr){ return false; }
		myNode_m = myNode_m->parent_m;
		return true;
	}
	bool goNextSibling()
	{
		if (isNull()){ return false; }
		if (myNode_m->next_sibling_m == nullptr){ return false; }
		myNode_m = myNode_m->next_sibling_m;
		return true;
	}
	bool goPrevSibling()
	{
		if (isNull()){ return false; }
		if (myNode_m->prev_sibling_m == nullptr){ return false; }
		myNode_m = myNode_m->prev_sibling_m;
		return true;
	}
	bool goFirstChild()
	{
		if (isNull()){ return false; }
		if (myNode_m->first_child_m == nullptr){ return false; }
		myNode_m = myNode_m->first_child_m;
		return true;
	}
	bool goLastChild()
	{
		if (isNull()){ return false; }
		if (myNode_m->last_child_m == nullptr){ return false; }
		myNode_m = myNode_m->last_child_m;
		return true;
	}
	T& operator*() const
	{
		return *myNode_m->key_m;
	}
	T* operator->() const
	{
		return &(operator*());
	}
	bool operator==(const BaseIterator iterator)
	{
		if (isNull() || iterator.isNull()){ return false; }
		return myNode_m->key_m == iterator.myNode_m->key_m;
	}
	bool operator!=(const BaseIterator iterator)
	{
		return !operator==(iterator);
	}
};

template<typename T>
class PreOrderIterator : public BaseIterator<T>
{
	friend class Tree<T>;
	PreOrderIterator(){}
public:
	explicit PreOrderIterator(TreeNode<T>* node) : BaseIterator<T>(node){}
	PreOrderIterator &pre_order_increment()
	{
		if (isParent()) {
			goFirstChild();
		}
		else {
			while (isLast()) {
				if (!goParent()){ break; }
			}
			goNextSibling();
		}

		return *this;
	}
	PreOrderIterator &pre_order_decrement()
	{
		if (isFirst()){
			goParent();
		}
		else{
			goPrevSibling();
			while (!isLeaf()) {
				if (!goLastChild()){ break; }
			}
		}

		return *this;
	}

	PreOrderIterator &operator++(){ return pre_order_increment(); }
	PreOrderIterator &operator++(int)
	{
		++(*this);
		return *this;
	}
	PreOrderIterator &operator--(){ return pre_order_decrement(); }
	PreOrderIterator &operator--(int)
	{
		--(*this);
		return *this;
	}
};

/*
template<typename T>
class PostOrderIterator :
	public std::iterator<std::bidirectional_iterator_tag, T>,
	public BaseIterator<T>
{
	friend class Tree<T>;
	PostOrderIterator() : myNode_m(nullptr){}
public:
	explicit PostOrderIterator(TreeNode<T>* node) : myNode_m(node){}
	PostOrderIterator &postorder_increment()
	{
		if (isParent()) {
			goFirstChild();
		}
		else {
			while (isLast()) {
				if (!goParent()){ break; }
			}
			goNextSibling();
		}

		return *this;
	}
	PostOrderIterator &postorder_decrement()
	{
		if (isFirstChild()){
			goParent();
		}
		else{
			goPrevSibling();
			while (!isLeaf()) {
				if (!goLastChild()){ break; }
			}
		}

		return *this;
	}

	PostOrderIterator &operator++(){ return postorder_increment(); }
	PostOrderIterator &operator++(int)
	{
		++(*this);
		return *this;
	}
	PostOrderIterator &operator--(){ return postorder_decrement(); }
	PreOrdPostOrderIteratorerIterator &operator--(int)
	{
		--(*this);
		return *this;
	}
};
*/

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
	Tree()
	{
		initialize();
	}
	Tree(const Tree& t)
	{
		initialize(); 
		copy(t.begin(), t.end());
	}
	~Tree()
	{
		finalize();
	}
	Tree& operator=(const Tree& t)
	{
		if (this != &t) {
			this->~Tree();
			new (this) Tree(t);
		}
		return *this;
	}
	void clear()
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
	bool empty() const { return head_m->next_sibling_m == tail_m; }
	size_t size() const { return nodeMap_m.size(); }
	size_t height() const
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

	pre_order_iterator begin() const { return pre_order_iterator(head_m->next_sibling_m); }
	pre_order_iterator rbegin() const { return --end(); }
	pre_order_iterator end() const { return pre_order_iterator(tail_m); }
	pre_order_iterator rend() const { return pre_order_iterator(head_m); }
	pre_order_iterator insert_root(const T &key)
	{
		clear();
		return insert_sibling(pre_order_iterator(head_m), key);
	}
	pre_order_iterator insert_parent(pre_order_iterator child, const T &key)
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
	pre_order_iterator insert_sibling(pre_order_iterator sibling, const T &key)
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
	pre_order_iterator insert_child(pre_order_iterator parent, const T& key)
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

	pre_order_iterator find(const T& key)
	{
		typename std::map<T, TreeNode<T>*>::iterator itr = nodeMap_m.find(key);
		if (itr != nodeMap_m.end()) {
			return pre_order_iterator(itr->second);
		}
		else{
			return end();
		}
	}
	void erase(pre_order_iterator pos)
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
	pre_order_iterator move(pre_order_iterator dst, pre_order_iterator src,
		MoveDirection dir)
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
protected:
	void disconect(pre_order_iterator &src){
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
	void connectToNextSibling(pre_order_iterator &dst, pre_order_iterator &src)
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
	void connectToPrevSibling(pre_order_iterator &dst, pre_order_iterator &src)
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
	void connectToFirstChild(pre_order_iterator &dst, pre_order_iterator &src)
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
	void connectToLastChild(pre_order_iterator &dst, pre_order_iterator &src)
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
	void initialize()
	{
		head_m = new TreeNode<T>();
		tail_m = new TreeNode<T>();

		head_m->next_sibling_m = tail_m;
		head_m->prev_sibling_m = head_m;
		tail_m->prev_sibling_m = head_m;
		tail_m->next_sibling_m = tail_m;
	}
	void finalize()
	{
		clear();
		delete head_m; head_m = nullptr;
		delete tail_m; tail_m = nullptr;
	}
	void copy(pre_order_iterator &begin, pre_order_iterator &end)
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
};

