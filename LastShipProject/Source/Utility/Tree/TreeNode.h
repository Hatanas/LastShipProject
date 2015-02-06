#pragma once

template<typename T>
class TreeNode
{
public:
	TreeNode<T>* parent_m;
	TreeNode<T>* firstChild_m;
	TreeNode<T>* lastChild_m;
	TreeNode<T>* prevSibling_m;
	TreeNode<T>* nextSibling_m;
	T* key_m;
public:
	TreeNode();
	TreeNode(const T& key);
	~TreeNode();
};


template<typename T>
inline TreeNode<T>::TreeNode()
{
	parent_m = firstChild_m = lastChild_m = prevSibling_m = nextSibling_m = nullptr;
	key_m = new T();
}

template<typename T>
inline TreeNode<T>::TreeNode(T const &key)
{
	parent_m = firstChild_m = lastChild_m = prevSibling_m = nextSibling_m = nullptr;
	key_m = new T(key);
}

template<typename T>
inline TreeNode<T>::~TreeNode()
{
	delete key_m;
	key_m = nullptr;
}

